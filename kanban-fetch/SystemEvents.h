/*
 * SystemEvents.h
 */

#import <AppKit/AppKit.h>
#import <ScriptingBridge/ScriptingBridge.h>


// The application's top-level scripting object.
@interface SystemEventsApplication : SBApplication

- (SBElementArray *) documents;
- (SBElementArray *) windows;

@property (copy, readonly) NSString *name;  // The name of the application.
@property (readonly) BOOL frontmost;  // Is this the active application?
@property (copy, readonly) NSString *version;  // The version number of the application.

- (id) open:(id)x;  // Open a document.
- (BOOL) exists:(id)x;  // Verify that an object exists.
- (void) abortTransaction;  // Discard the results of a bounded update session with one or more files.
- (NSInteger) beginTransaction;  // Begin a bounded update session with one or more files.
- (void) endTransaction;  // Apply the results of a bounded update session with one or more files.
- (void) logOut;  // Log out the current user
- (void) restart;  // Restart the computer
- (void) shutDown;  // Shut Down the computer
- (void) sleep;  // Put the computer to sleep
- (void) keyCode:(id)x using:(id)using_;  // cause the target process to behave as if key codes were entered
- (void) keystroke:(NSString *)x using:(id)using_;  // cause the target process to behave as if keystrokes were entered

@end


// The System Events application
@interface SystemEventsApplication (ProcessesSuite)

- (SBElementArray *) applicationProcesses;
- (SBElementArray *) deskAccessoryProcesses;
- (SBElementArray *) processes;
- (SBElementArray *) UIElements;

@property (readonly) BOOL UIElementsEnabled;  // Are UI element events currently being processed?

@end
