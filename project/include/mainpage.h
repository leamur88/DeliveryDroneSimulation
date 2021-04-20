/** \mainpage CSCI 3081 Delivery Simulation project
 * 
 * ###Running the Program############
 * 
 * **Note: This program is meant to only be run on a UMN CSE Labs Machine**
 * 
 * *The following instructions are for those using VOLE3D or are physically at the lab. Not intended for all SSH use.*
 * 1. Navigate to the `project` directory
 * 2. In the terminal, run `make clean` followed by  `make` to ensure that the project builds correctly
 * 3. Open up a preferred browser, Chrome works best, and go to "127.0.0.1:8081" 
 * 4. In the terminal, still in the project directory, type `bash ./bin/run.sh` to run the simulation
 * 5. Rarely, the simulation is built incorrectly and only the drone and customer spawn in. If this occurs please go back to step 2. (You will know this occurs if the customer is in the packages position)
 * 6. Optionally, if you to run the test files type `make test` followed by `bash ./bin/test.sh`
 * 7. Last, if you want to regenerate this documentation, navigate to `project/docs` and run `doxygen Doxyfile`. The html will be updated and you can refresh your page
 *
 * Within the program itself you can change the simulation speed with the provided slider and change the view of which entity you are following. In its current state,
you should expect to see the drone fly over all of the buildings, following a beeline trajectory to the packages location. Once there, the drone will hover over the package for a second, pick
up the package, and travel in unison to the customer. Once at the customer, the package will dissapear after a second (i.e. the customer will take the package), and the simulation is done. Remember to 
kill the program to ensure that the IT folks won't send you an angry e-mail.
* 
* ###Composite Factory vs. Abstract Factory vs. Concrete Factory
* 
* 
* ####Composite Factories
* ![Basic Composite Factory Pattern](../CompositePattern.png)
* 
* Composite factory patterns are perfect when you want to treat a group of objects as one object. This allows for you to preform a task on a group of "children," as described in the picture above, by only doing one command.
* This allows us to not have to individually call a function on a group of like-minded objects or have a bunch of if statements to ensure you are calling the right one. Instead, this is handled by a for loop and other checks within the composite factory.
* This also makes control flow very apparent and almost makes it so you can have a facade for the functions you want to call on said group of children. 
* Unforetunately, like all great things in life there is still a downside to composite factory patterns. Composite factories 
* are only really useful if you want each child to preform the same operation. If you need each child to preform a different operation then you are stuck with the same if, else if's that the factory gets rid of.
* You would also need to change the "Component" Interface to align with the new operation, causing you to need to implement the operation in all of the children.
* Since we simply want all of our factories to do the same task, create an entity, then it works perfectly. Anything more complicated should be, and is handled by other classes.
* 
* 
* 
* ####Abstract Factories
* ![Basic Abstract Factory Pattern](../AbstractFactory.png)
*  
* Abstract Factories are best used when implementing polymorphism. Although this does require an intermediary factory for each object, it keeps things extremely well organized.
* As shown above, you need to create a seperate factory for every single type of object. Although this does become tiresome, the benefits of using polymorphism to generate your entities
* far outweighs the potential downsides. This should be used when there are no set limits on what you will be creating. It makes it much easier to add objects as a project progresses while not needing to affect 
* previously written code. 
* 
* ####Concrete Factories
* ![Basic Concrete Factory Pattern](../ConcreteFactory.png)
* 
* Concrete Factories are great when all of the requirements are predetermined. If it is already known how many objects are needed, the types of objects, and exactly what they will do, then it would make sense 
to use a concrete factory. Theoretically, since they don't rely on polymorphism and are direct, concrete factories should be faster than the other factory patterns. On the other hand, the slight speed boost and possibile increase
in readability normally does not make up for how much this limits you. In a concrete factory pattern, like the one pictured above, once you start adding more types of objects, the factory can get very messy. Let's say
you were to add 5 more types of ducks. In that case, you would need to have 5 additional if statements within the duck factory and it becomes harder and harder to manage. You should only really use a concrete factory when
the number, and types of items you plan on generating rarely changes.
* 
* 
* 
* ###Our Composite Factory Pattern Implementation
* ![Our Composite Pattern Implementation](../CompositePatternUML.png)
*  
* In our case, a mixture of Composite and Abstract factory patterns is excellent. As mentioned prior, composite factory patterns are best used when preforming the same operation on a group of objects, which is exactly what we did. Additionally,
* since we are creating a multitude of entities, the abstract factory pattern makes it really easy to follow the control flow and utilize polymorphism.
* Our composite factories main purpose, for now, is simply to create other entities by calling the `createEntity` function on all of the other factories. This makes it extremely easy to use within the Delivery Simulation class. On top of that, it utilizes polymorphism,
* and is easy to follow. There are some downsides to implementing it like this. For starters, debugging can be a bit of a nightmare. Because I had to parse through, and set breakpoints at, multiple files,
* it took me longer than I thought to find some segmentation faults. Another downside is that you cannot add much more functionality to these classes. This is both a pro and a con because once you have a factory working you never have to update it,
* but it also limits you to what you can do with it. If we were to want to add additional functionality, you would need to change the "component," or our IEntity Factory Interface, and implement it across all of the child factories. 
* Nevertheless, our composite factory pattern is perfect for what we want it to do, so the benefits clearly outweighed the negatives.
*
*
*
* ###Group Member Roles for Iteration 2
*   Development Lead - David\n
*   Scheduler - Jon\n
*   Reporter - Jules\n
*   Project Manager - Varun\n
*
*
* ####Team Meeting on 3/28: 
* We started the meeting by discussing whose code should be used to move forward with iteration 2.  
* After careful consideration, we decided Jon's code should be used.This is because although he was missing some aspects that needed to be added for iteration 2, 
* he had a solid codebase that would allow for seamless improvements.  Each group member had parts of their code which they could add to Jon's soon after. 
* For David it was the smartpath he had already implemented in iteration 1.  For Varun and Jules it was changing the update functions in drone and delivery simulation 
* so the specific updating happened in drone and the delivery simulation update function simply handled all of the drones.  We also went through the steps of a github 
* pull request together to make sure we understood the process.  Finally, we assigned all of the issues for the first deliverable according to interest and our 
* implementation for iteration 1.  David was assigned the implementation of the smartpath.  Jules was assigned the observer pattern.  Jon was assigned
* the delivery objects implementation and created the robot class.  Varun was assigned to update function in drone.

* ####Team Meeting on 3/29: 
* This meeting was fairly brief. We spent the beginning part of the meeting fixing merge conflicts caused by changes in Varun and David’s 
* new code addition to the Drone. Once that was complete, we created the pull request and ensured that the code within devel was still functioning properly. We 
* determined that our next steps should include finishing the first deliverable of this iteration. This included assigning Varun to implement the drone actually
* ascending and descending when picking up the package. Jules was assigned to update the robot factory based on the changes made with the robot class. David was 
* assigned to create a pseudo implementation of the strategy pattern within the Drone class. We refer to this as a “pseudo” implementation because at this point 
* we still had not learned about the strategy pattern but the switch statements David implemented to choose which update function to use ended up being similar to 
* a strategy pattern. Jon was assigned to update the Delivery Objects header file to limit repeated code in both Robot and Drone. 
*
* ####Team Meeting on 3/30: 
* This meeting was when final jobs for deliverable 1 were assigned.  Jules was assigned to the observer pattern.  Jon was assigned 
* drone google tests and Varun was assigned the others.  Varun and Jon were also assigned to help out where needed.  We also approved pull requests for Jon’s
* delivery objects implementation.  Jules also confirmed the design of the observer pattern with the group prior to implimentation. Future work times were 
* planned, with 3/31 blocked for working on multiple packages and 4/1 for the observer pattern.  Jon and Varun would help with both.  
* 
* 
* ####Team Meeting on 4/5: 
* This meeting we began discussing and creating a plan to complete deliverable 2. We read through the documentation to decide which stuff
* we needed to implement. We created new issues for deliverable 2 based on the documentation for the deliverable. Based on this we decided that the battery objective
* was the main priority. This was assigned to David and Varun to work through. On top of that, the second priority was deciding how to implement a strategy pattern 
* for the update function. We decided to switch our update function to solely work with two path variables and to create those variables within the different patterns.
* The setting up of this structure and implementing the beeline path was assigned to Jon. Last, Jules began creating teamwork documentation. This would give us 
* a head start on the large amount of documentation work still to come.
*
* ####Team Meeting on 4/7: 
* This meeting we discussed our plan to finish the implementation of all deliverable 2 functionalities. At this point the strategy pattern 
* structure was implemented and the Drone was correctly being assigned packages if another one died. We realized our final functionalities yet to be implemented were
* the smart path class, the parabolic class path, and having the package drop to its original y value if the drone/robot ran out of battery. Jules was assigned the
* parabolic path and Varun was assigned the smart path. Jonathan was assigned to assist them as he had background knowledge on how to implement the different paths
* within the strategy pattern. Last, David was in charge of getting the package to drop down to its original height in the simulation once the drone/robot had “dropped” it.
* 
* ####Team Meeting 4/16
* During this meeting we planned how to complete the last steps for iteration two. At this point we have finished all of the functionality and need to solely focus on completing 
* the documentation of our project. Although the Doxygen page was already created and fairly full, we still needed to add a couple more discussions to the mainpage. For that, Jules 
* was assigned to discuss the observer pattern implementation and Jon was assigned to discuss the strategy pattern and route implementation. On top of that, there were some google tests 
* that still needed to be updated. For that, David was assigned to create google tests for the observers, Varun was assigned to create tests for the beeline path, Jules was assigned to 
* create a test for the parabolic path. Additionally, Jon was assigned to update the Drone tests, and David was tasked to ensure all of the other previously written tests were up to standard.
*
*
* ###Strategy Pattern/Route Implementation\n
* Before starting this deliverable, we simply had two update functions, one for smartpath and one for beeline. We quickly found out through the TA’s that our approach for 
* the beeline specifically was extremely unorthodox. Instead of having a vector of float vectors containing our destination points, we would manually generate every point 
* when it got to that stage. For example, when the drone had to descend we had a descend function that would check a couple boolean values to determine what the next point the 
* drone needed to go to was. This ended up being an extremely clunky process that the strategy pattern forced us to change. Once implementing the strategy pattern, we got rid of more 
* than 75% of the methods within our drone class and it made everything a lot easier to follow.
*
* Before we get too ahead of ourselves, let’s quickly review what the strategy pattern is. Using material from lab 14, like the UML diagram pictured below, our team got a good grasp of how to implement it.
*
* ![Basic Strategy Pattern](../StrategyPattern.png)
* The first thing we noticed about the strategy pattern is that it took a lot of the code complexity away from the drone class itself. For our purpose, the “context” would be either the 
* drone or robot class and the “strategy” would be the interface that created our path. At this point we came to the realization that we could have the beeline path strategy update the path to the package 
* and the path to the customer the same way the smart path did. By accessing the customerRoute and packageRoute variables through a drone/robot pointer in the strategies, we could update the path using the 
* strategy pattern. Since we already had the structure to have the drone and robot’s cycle through two separate vectors of float vectors (customerRoute and packageRoute), the beginning of implementing the strategy pattern was straightforward. 
*
*
* We created a new interface called deliverypaths.h along with three concrete strategy classes: beelinepath.cc, smartpath.cc, and parabolicpath.cc. As aforementioned, these classes simply had one update function which updated the delivery objects 
* customerRoute and packageRoute. The smartpath routes were determined by the iGraph object in the delivery object so those routes were freebies when implementing the smartpath object. Similarly, the beeline path’s route was simple to implement since 
* each route only had 4 basic points, all of which were always accessible through the drone class. (Note: to make our code more legible, we created a helper function in parabolic path that would create the path based on two endpoints)
*
* ![Our Strategy Pattern](../Path_interaction.png)
* The strategy class chosen would be determined by the Json object. In our Drone constructor we would check what the “path” variable was set to and instantiate that concrete strategy as our path. Once a package was added to the Drone, the concrete strategies 
* update function was called and then the Drone’s position was updated normally. The robot was even easier to implement since it just had to have the smartpath strategy. Therefore the smartpath object was always instantiated in the constructor and was called upon 
* when a package was set for the Robot. 
*
* The hardest part about this route implementation was the parabolic path. The first part of creating the path is to split up the beeline path into 100 equal parts on the xz plane. This was pretty simple to create with a for loop. The hard part is the changing of 
* the y value of the drone’s position. A very useful tool was lab14. Lab 14 gave us the perfect formula to implement the path. (Note: All of the vectors below are 3D vectors where their xyz values replicate the normal xyz values if the beeline path was split up into 100 intervals).
*
* Y = (1 - ( distance(V,Vm)^2 ) / ( distance(Vi,Vm)^2 )) *j
*
* V = next vector in the path\n
* Vm = Midpoint\n
* Vi = initial vector of the path\n
* j = Maximum height of the desired parabola\n
*
* As you can see, the formula is quite simple. Some important tips to keep in mind, make sure that you are referencing the initial and end points as 3D points. It is important to keep the difference in those two y values 
* so they can be used in the calculation for the new Y value. Without it, the drone will always try to pick up the package a couple of units too high.
*
* ###Observer Pattern Implementation\n
* The observers are first created within delivery_simulation.cc by calling AddObserver.  The observers are then put into an observer vector which each drone and robot has.
* This is done after these vectors are cleared to make sure no leftover observers remain in them.  This way we can loop through all of an object’s observers whenever OnEvent 
* needs to be called.  The statuses that the observer needs are stored in booleans in drone and robot so OnEvent can be easily called.  The path is stored as a member
* variable for the same reason.  Using this method, statuses such as delivered, scheduled, and enroute as well as the path can all be passed to the observers easily because
* these attributes are within the delivery objects classes. It should be noted that the file deliveryobjects.h, which drone and robot inherit from, contains the functions
* they use for setting and removing observers as well as managing the various attributes that are passed to the observers.  This is because the functionality of these 
* functions and attributes remain the same between drone and robot.  
*
*
*
*
*
*
 */
