#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include "main.h"
#include "GLlog.h"
#define GL_LOG_FILE "gl.log"


//opens log file. prints name and date at the top and close the file afterwards.
bool restart_gl_log() 
{
	FILE* file = fopen(GL_LOG_FILE, "w"); if (!file) 
	{
		fprintf(stderr,"ERROR: could not open GL_LOG_FILE log file %s for writing\n", GL_LOG_FILE); return false;
	} 
	time_t now = time(NULL); 
	char* date = ctime(&now); 
	fprintf(file, "GL_LOG_FILE log. local time %s\n", date); 
	fclose(file); 
	return true;
}
//opened in append mode(add a line tothe end) it is the main log print out. can take any number of variables and adds them to the end. and closes the file again
bool gl_log(const char* message, ...)
{
	va_list argptr;
	FILE* file = fopen(GL_LOG_FILE, "a");
	if (!file)
	{
		fprintf(
			stderr,
			"ERROR: could not open GL_LOG_FILE %s file for appending\n",
			GL_LOG_FILE);
		return false;
	}
	va_start(argptr, message);
	vfprintf(file, message, argptr);
	va_end(argptr);
	fclose(file);
	return true;
}

//same as the function above but outputs error messages to the console (or terminal)
bool gl_log_err(const char* message, ...) {
	va_list argptr;
	FILE* file = fopen(GL_LOG_FILE, "a");
	if (!file) {
		fprintf(
			stderr,
			"ERROR: could not open GL_LOG_FILE %s file for appending\n",
			GL_LOG_FILE
		);
		return false;
	}
	va_start(argptr, message);
	vfprintf(file, message, argptr);
	va_end(argptr);
	va_start(argptr, message);
	vfprintf(stderr, message, argptr);
	va_end(argptr);
	fclose(file);
	return true;
}
//If I print my error message
//to stderr it should pop up as soon as it occurs, which can make it obvious when something has gone
//wrong.
/*Error Checks
We can start GLFW in the same way as before, but add some extra checks. This will tell us if we've
made a mistake such as calling a GLFW function with the wrong parameters. Before initialising
GLFW, we can set up an error callback, which we can use to spit out some error information, then
exit the programme. We create a little function for the callback:
void glfw_error_callback (int error, const char* description) {
gl_log_err ("GLFW ERROR: code %i msg: %s\n", error, description);
}
This will tell is if there was a special problem initialising GLFW.
int main () {
if (!restart_gl_log ()) { /* quit?  }*/
/* start GL context and O/S window using the GLFW helper library
gl_log("starting GLFW\n%s\n", glfwGetVersionString());
// register the error call-back function that we wrote, above
glfwSetErrorCallback(glfw_error_callback);
if (!glfwInit()) {
fprintf(stderr, "ERROR: could not start GLFW3\n");
return 1;
} */
