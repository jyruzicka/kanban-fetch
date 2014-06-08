/*
 * OmniFocus.h
 */

#import <AppKit/AppKit.h>
#import <ScriptingBridge/ScriptingBridge.h>


@class OmniFocusApplication, OmniFocusDocument, OmniFocusProject, OmniFocusTask, OmniFocusFlattenedTask, OmniFocusFlattenedProject;

enum OmniFocusProjectStatus {
	OmniFocusProjectStatusActive = 'FCPa' /* Active */,
	OmniFocusProjectStatusOnHold = 'FCPh' /* On Hold */,
	OmniFocusProjectStatusDone = 'FCPd' /* Done */,
	OmniFocusProjectStatusDropped = 'FCPD' /* Dropped */
};
typedef enum OmniFocusProjectStatus OmniFocusProjectStatus;

@interface OmniFocusApplication : SBApplication
- (OmniFocusDocument *) defaultDocument;
@end

@interface OmniFocusDocument : SBObject
- (SBElementArray *) flattenedProjects;
- (SBElementArray *) flattenedTasks;
@end

@interface OmniFocusSection : SBObject
@end

@interface OmniFocusProject : OmniFocusSection
- (NSString *) id;
- (NSString *) name;

- (OmniFocusTask *)rootTask;
- (OmniFocusProjectStatus) status;
- (id) container;
- (id) startDate;
- (BOOL) completed;
@end

@interface OmniFocusTask : SBObject

- (NSString *) id;
- (NSString *) name;

- (SBElementArray *)flattenedTasks;

- (id) startDate;
- (id) context;
@end

@interface OmniFocusContext : SBObject
- (NSString *) name;
@end


@interface OmniFocusFlattenedTask : OmniFocusTask
@end

@interface OmniFocusFlattenedProject : OmniFocusProject
@end