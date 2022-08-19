# CS-300-DSA-ABCU-Course-Planner

## What was the problem you were solving in the projects for this course?
The projects for this course focused on creating a Course Planner application for ABC University. We were to
load a file containing a course schedule and parse the courses, course title and prerequisites for each entry.

In this course, we had two projects. The first project was to create the pseudo code and run-time analysis of
our data structures that were considered for this project. Once we had these items, we were to make a recommendation
for a data structure to use for the application. The second project focused on the actual implementatino of our
pseudocode into a working application. This application was to sort the course alphanumerically and have the
ability to print all course or a specific course.

## How did you approach the problem? Consider why data sctructures are important to understand. I approached the 
problem by implementing a binary search tree. The reason for this was because of the increased efficiency when 
searching for a course, which has a time complexity of O(logn), and the fact that the algorithm to insert courses
into the binary search tree makes sure that the tree is already sorted. It is important to understand data structures
as they play a very important part in the efficiency of your applications. Using the wrong data structure for the wrong
use-case can cause very real performance issues in an application. If you have millions of items of data that are
unsorted, and you have a need to sort this data, a vector may not be the most suitable option. A hash table may
also not be suitable, as hash tables are not a sorted data type, thus would required impplementing an auxillary
data type alongside the hash table for sorting.

## How did you overcome any roadblocks you encounted while going through the activities or project?
For me, the largest roadblock was time. I am currently working fulltime while attending university fulltime and
trying to be an attentive father and husband. Time is a resource I have very little of. Prioritizing what needed
to be done for each class on each day was an absolute necessity to finishing this course.

## How has your work on this project expanded your approach to designing software and developing programs?
This course has definitely made me think more about the runtime complexity of my algorithms and functions when I am
writing code for work. Previously, I had some desire to be efficient, but now that I am able to actually calculate
the time complexity and storage complexity for my applications, I feel I can actually prove the efficiency of what
I am creating.

## How has your work on this project evolved the way you write programs that are maintanable, readable, and adaptable?
I've always tried to maintain as much maintainability and portability as I can in my applications that I write. As
shown in this project, I enjoy using classes when possible. A class implemented may only be relevant to the application
you are currently writing, or it may very well be suitable for a library that can be included in additional projects.
Making sure that code is easily readible and easy to maintain makes using the code in the future much easier.
