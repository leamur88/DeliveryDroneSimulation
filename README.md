# Drone Delivery Simulation

## Background
This was a project made by my partners and I in CSCI 3081W (Program Design and Development) at the University of Minnesota. During this class we were given a baseline and instructed to implement a drone simulation that would go around the virtual UMN campus and deliver packages to customers. Once a basic beeline delivery was implemented, we had to make the drone have the ability to deliver using a parabolic route and using a 'smart' route (using streets). Lastly, we added some physics components (Drone will move slower proportionally to how much weight it is carrying), and the ability to have multiple drones deliver to multiple customers. Because we added multiple drones, we also added the ability for a drone to pick up a different drones package in the event that it runs out of battery before making a delivery.

## Running Different Simulations
In the run shell script (project/bin/run.sh) you will see that there is a 'SCENE' variable that is set. This variable determines what simulation will run. You can choose any of the 4 listed in the file, or you can choose from many more in the project/web/scenes folder. All scenes should be working and can show off the different abilities of our simulation!

## Running the simulation
To run the simulation, you must use docker and follow the instructions below:

### Getting Started with Docker

1. Build docker image

    ```bash
    bin/build-env.sh
    ```

2. Run docker image

    ```bash
    #Usage bin/run-env.sh <port - optional(default 8081)>
    bin/run-env.sh
    ```
    
3. Build project web server (inside docker image) NOTE: You won't be able to `cd` here yet because the project directory does not exist. If you were able to launch the above commands you should now be inside the docker image. You can exit it with CTRL+D now.

    ```bash
    # Inside docker image
    cd /home/user/repo/project
    make
    ```
    
4. Run web server (inside docker image)

    ```bash
    # MUST be within project/ directory inside docker image
    cd /home/user/repo/project
    ./bin/run.sh
    ```
    
5. Open up any brower and go to http://127.0.0.1:8081/


