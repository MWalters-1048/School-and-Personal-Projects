#include <string.h>
#include <stdio.h>
#include <stdlib.h>		// For built-in malloc that returns void *

#include "Dictionary.h"
#include "Enrollment.h"

// create global dictionaries
dictionary	CourseDict;
dictionary	StudentDict;

// -------------------------------------------
// adds *e to the CourseDict.
// Checks if *e already exists, if so print error message
// and don't update the dictionary.  Else update dictionary.
// -------------------------------------------
void addCourse( course_element *e )
{
	// check if course already exists in dictionary else print message
	// if not, insert to course dict
	if (insert(&CourseDict, (element*)e)) {
		puts("Course already exists");
		return;
	}

}

// -------------------------------------------
// deletes course whose ID/key is c_key from the CourseDict.
// This should check if the course to be deleted exists.
// If not, just print an error message: "Course does not exist."
// If the course exists, then this will also drop students who
// are currently enrolled in the course and then remove course
// from course dict
// -------------------------------------------
void delCourse( char *c_key )
{
	node_t* node = find(&CourseDict, c_key);
	// check if course is in the dict - if not, print error and return
	if (!node) {
		puts("Course does not exist.");
		return;
	}


	// get course info from the corresponding node
	// loop over the list of students enrolled in course and drop them
	// NOTE: be careful because you are looping over the same list -
	// you are removing elements from
	course_value* course = node->value;
	node_t* s = course->list;
	node_t* tmp = s;
	while (s) {
		tmp = s->next;
		drop(s->key, c_key);
		s = tmp;
	}

	// delete course with given key from dictionary
	delete(&CourseDict, c_key);

	printf("Element with key %s removed\n", c_key);

	
}

// -------------------------------------------
// enrolls student into course. params are s_key and c_key
// Need to check for: existence of course, and if student
// is already enrolled in the course.  Also check if course
// is full or if student has reached max number of courses.
// If there's any error, print a message and don't enroll
// the student.  If there's no errors, update both dictionaries.
// -------------------------------------------
void enroll( char *s_key, char *c_key )
{
	// declare vars for nodes coressponding to course entry and student entry
	// in respective dictionaries
	node_t *student_node, *course_node;

	// decalare vars for course info and student info corresponding to
	// the value fields of each node/element
	// initialize student info to NULL
	course_value* course = NULL;
	student_value* student = NULL;

	// declare course and student node corresponding to list of courses
	// in a student's node and students in a course's node	
	node_t* students;
	node_t* courses;

	
	// fetch course and student corresponding to keys from respective dicts
	// initialize vars depending on whether student/course with given key
	// is in the dictionary
	
	// if course doens't exist, print error and return
	course_node = find(&CourseDict, c_key);
	// check if course is in the dict - if not, print error and return
	if (!course_node) {
		puts("Course does not exist.");
		return;
	}
	course = course_node->value;

	student_element se;

	student_node = find(&StudentDict, s_key);
	if (student_node) {
		student = student_node->value;

		memcpy(se.key, s_key, 5);
		se.value = student;

		// if student already enrolled in '2' courses, print message and return
		if (student->num_courses == 2) {
			puts("Cannot enroll in more than 2 courses.");
			return;
		}

		// check if student is enrolled in the course. If so, print message and return
		if (findList(student->list, c_key)) {
			puts("Student already enrolled.");
			return;
		}
	} else {
		student = calloc(1, sizeof(student_value));

		memcpy(se.key, s_key, 5);
		se.value = student;

		// if student does not exist, insert student to student dict
		insert(&StudentDict, (element*)&se);

		printf("Adding student: %s\n", s_key);
	}


	// check if student is enrolled in the course. If so, print message and return
	node_t* s = findList(course->list, s_key);
	if (s) {
		puts("Student already enrolled in that course");
		return;
	}

	// see if course is full
	if (course->num_students == course->capacity) {
		puts("Course is full.");
		return;
	}

	// if not, add student to the list (of students) in the course
	// HINT: instantiate a new node and assign it to the node corresp.
	// to student in course's list - initialize the node's fields and
	// insert it into the course's list of students enrolled in it
	// and update the course value fields
	student_node = calloc(1, sizeof(node_t));
	memcpy(student_node->key, s_key, 5);

	student_node->value = student;

	insertList(&course->list, student_node);
	course->num_students++;


	// otherwise, add node to the list of student's enrolled courses
	// HINT: again, instantiate a node (this will be the node of a course
	// in a student's list) and intialize the fields of that node

	course_node = calloc(1, sizeof(node_t));
	memcpy(course_node->key, c_key, 5);

	course_node->value = course;

	insertList(&student->list, course_node);
	student->num_courses++;
}

// -------------------------------------------
// drops a student from course. params are s_key and c_key
// Need to check for: existence of course, and if student
// is enrolled in the course.  If any error is encountered,
// print an error message.
// If there are no errors, update both dictionaries.
// -------------------------------------------
void drop( char *s_key, char *c_key )
{
	// fetch nodes corresponding to student and course from
	// respective dicts having the given keys
	node_t* student_node = find(&StudentDict, s_key);
	node_t* course_node = find(&CourseDict, c_key);


	// if found no such student or course, print message and return
	if (!student_node) {
		puts("No such student.");
		return;
	}

	if (!course_node) {
		puts("No such course.");
		return;
	}


	student_value* sv = student_node->value;
	// see if student is enrolled in the course
	node_t* c = findList(sv->list, c_key);
	if (!c) {
		puts("Student is not enrolled in that course.");
		return;
	}

	// delete course from student list
	deleteList(&sv->list, c);


	course_value* cv = course_node->value;
	node_t* s = findList(cv->list, s_key);
	// should always be non-NULL if c was valid

	// delete student from course list
	deleteList(&cv->list, s);


	// update counter fields
	sv->num_courses--;
	cv->num_students--;
}

// -------------------------------------------
// prints the StudentDict.
// -------------------------------------------
void printStudents()
{
	printf("Students:\n");
	print( &StudentDict );
}

// -------------------------------------------
// prints the CourseDict.
// -------------------------------------------
void printCourses()
{
	printf("Courses:\n");
	print( &CourseDict );
}

// -------------------------------------------
// Don't edit the code below.  This is the driver code to test
// your implementation.
// -------------------------------------------
int main()
{
	char	line[100];
	char 	*command;
	int	done = 0;

        course_element  *ce;
        student_element *se;

	char	*course_key;
	char	*student_key;

	// initialize dictionaries
	create( &CourseDict, 20 );
	create( &StudentDict, 20 );

	// process input
	while( ! done )
	{
		// read an entire line as a string
		fgets(line, 100, stdin);
		int len = strlen(line);
		line[len-1] = 0; //chop off newline to prevent problems

		// pulls command code, assume comma or tab separated
		command = strtok( line, " \t" );

		if (strcmp(command, "ex")==0)
			{	printf( "Exited Program\n" );
				done = 1;
			}
		else if (strcmp(command, "ac")==0)		// add a new course
			{
				// printf("ac\n");
				
				// Parse and package rest of line into a course_element
				ce = (course_element *) malloc( sizeof(course_element) );
				course_key = strtok( NULL, " " );
				printf( "Adding course: %s\n", course_key );
				memcpy( (*ce).key, course_key, 5 );
				ce->value = (void *) newNode( 'c' );
				ce->value->capacity = atoi( strtok( NULL, " " ) );
				ce->value->num_students = 0;
				ce->value->list = NULL;
				addCourse( ce );
				free(ce);
			}
		else if (strcmp(command, "dc")==0)		// delete a course
			{
				course_key = strtok( NULL, " " );
				delCourse(course_key);
				printf("Delete Course Complete\n");
			}
		else if (strcmp(command, "en")==0)		// enroll a student
			{
				// printf("en\n");
				
				// Parse and package rest of line into a course_element
				student_key = strtok( NULL, " " );
				course_key = strtok( NULL, " " );
				printf( "Enrolling student: %s into course: %s\n", student_key, course_key );
				enroll( student_key, course_key );
			}
		else if (strcmp(command, "dr")==0)		// drop a student
			{
				student_key = strtok( NULL, " " );
				course_key = strtok( NULL, " " );
				printf( "Dropping student: %s from course: %s\n", student_key, course_key );
				drop(student_key, course_key);
			}
		else if (strcmp(command, "ps")==0)		// print students
			printStudents();
		else if (strcmp(command, "pc")==0)		// print courses
			printCourses();
		else printf("Unrecognized command: %2s\n", command);


	}

	return 0;
}
