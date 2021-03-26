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
This allows us to not have to individually call a function on a group of like-minded objects or have a bunch of if statements to ensure you are calling the right one. Instead, this is handled by a for loop and other checks within the composite factory.
This also makes control flow very apparent and almost makes it so you can have a facade for the functions you want to call on said group of children. 
Unforetunately, like all great things in life there is still a downside to composite factory patterns. Composite factories 
are only really useful if you want each child to preform the same operation. If you need each child to preform a different operation then you are stuck with the same if, else if's that the factory gets rid of.
You would also need to change the "Component" Interface to align with the new operation, causing you to need to implement the operation in all of the children.
Since we simply want all of our factories to do the same task, create an entity, then it works perfectly. Anything more complicated should be, and is handled by other classes.
 * 
 * 
 * 
 * ####Abstract Factories
 * ![Basic Abstract Factory Pattern](../AbstractFactory.png)
 *  
 * Abstract Factories are best used when implementing polymorphism. Although this does require an intermediary factory for each object, it keeps things extremely well organized.
 As shown above, you need to create a seperate factory for every single type of object. Although this does become tiresome, the benefits of using polymorphism to generate your entities
 far outweighs the potential downsides. This should be used when there are no set limits on what you will be creating. It makes it much easier to add objects as a project progresses while not needing to affect 
 previously written code. 
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
since we are creating a multitude of entities, the abstract factory pattern makes it really easy to follow the control flow and utilize polymorphism.
Our composite factories main purpose, for now, is simply to create other entities by calling the `createEntity` function on all of the other factories. This makes it extremely easy to use within the Delivery Simulation class. On top of that, it utilizes polymorphism,
and is easy to follow. There are some downsides to implementing it like this. For starters, debugging can be a bit of a nightmare. Because I had to parse through, and set breakpoints at, multiple files,
it took me longer than I thought to find some segmentation faults. Another downside is that you cannot add much more functionality to these classes. This is both a pro and a con because once you have a factory working you never have to update it,
but it also limits you to what you can do with it. If we were to want to add additional functionality, you would need to change the "component," or our IEntity Factory Interface, and implement it across all of the child factories. 
Nevertheless, our composite factory pattern is perfect for what we want it to do, so the benefits clearly outweighed the negatives.
 */
