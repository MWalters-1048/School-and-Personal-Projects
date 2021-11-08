// -------------------------------
// Enrollment structs
//
// -------------------------------

typedef struct {
	int	capacity;		// course capacity
	int	num_students;	// number of students enrolled
	node_t	*list;		// list of students in course
	} course_value;

typedef struct {
	int	num_courses;	// number of courses enrolled in
	node_t	*list;		// list of courses student is enrolled in
	} student_value;

typedef struct {		// key:value pair for a course
	char		key[5];
	course_value	*value;
	} course_element;

typedef struct {		// key:value pair for a student
	char		key[5];
	student_value	*value;
	} student_element;


// -----------------------------
// Creates a node for a course or student value field
// -----------------------------
node_t *newNode( char type )
{
	if (type == 'c')
		return ( malloc( sizeof(course_value) ) );
	else if (type == 's')
		return ( malloc( sizeof(student_value) ) );
}

// -------------------------------------------
// adds e to the CourseDict.
// -------------------------------------------
void addCourse( course_element *e );


// -------------------------------------------
// deletes course whose ID is c from the CourseDict.
// -------------------------------------------
void delCourse( char *c_key );

// -------------------------------------------
// enrolls student into course. params are s_key and c_key
// -------------------------------------------
void enroll( char *s_key, char *c_key );

// -------------------------------------------
// drops student from course. params are s_key and c_key
// -------------------------------------------
void drop( char *s_key, char *c_key );

// -------------------------------------------
// prints the StudentDict. 
// -------------------------------------------
void printStudents();

// -------------------------------------------
// prints the CourseDict. 
// -------------------------------------------
void printCourses();


       
