Feature: A time service will be used to get the current time by hiding the 
    complexity of different implementations behind a simple interface.

Scenario: Create a service instance which can execute asynchronous requests
    Given that the service can use asynchronous requests
    When a time service instance was created
    Then it should be set to run asyncronously
    And the primary server should set to localhost
    And the alternate server list should be empty

Scenario: Create a service instance which can only execute synchronous requests
    Given that the service can't use asynchronous requests
    When a time service instance was created
    Then it should be set to run synchronous requests
    And the primary server should set to localhost
    And the alternate server list should be empty

Scenario: Change the execution behaviour
    Given that the service <CanUseAsynchronousDNS>
    When the asynchronous behaviour is set to the <Input>
    Then the new state should be the <Result>
    |Input|CanUseAsynchronousDNS|Result|
    |false|false|false|
    |false|true|false|
    |true|false|false|
    |true|true|true|

Scenario: Change the primary server before starting the service
    Given that the service isn't running
    When the primary server is set
    Then it will change the primary server value
    And return a success

Scenario: Change the primary server after starting the service
    Given that the service is running
    When the primary server is set
    Then it will return a failure      

Scenario: Add an alternate server before starting the service
    Given that the service isn't running
    When a alternate server is added
    Then add the hostname to the list
    And return a success

Scenario: Add an alternate server after starting the service
    Given that the service is running 
    When a alternate server is added
    Then return a failure

Scenario: Start a not running service
    When start the service
    Then it should change into the running state
    Else it should do nothing

Scenario: Try to start an already running service
    When start the service
    Then it should do nothing