/*
 * OmniFocus2.h
 */

#import <AppKit/AppKit.h>
#import <ScriptingBridge/ScriptingBridge.h>


@class OmniFocus2Application, OmniFocus2Document, OmniFocus2Window, OmniFocus2DocumentWindow, OmniFocus2Setting, OmniFocus2FocusSections, OmniFocus2Section, OmniFocus2Folder, OmniFocus2Context, OmniFocus2Project, OmniFocus2Task, OmniFocus2AvailableTask, OmniFocus2RemainingTask, OmniFocus2InboxTask, OmniFocus2FlattenedTask, OmniFocus2FlattenedProject, OmniFocus2FlattenedFolder, OmniFocus2FlattenedContext, OmniFocus2Perspective, OmniFocus2Tree, OmniFocus2QuickEntryTree, OmniFocus2SidebarTree, OmniFocus2ContentTree, OmniFocus2InboxTree, OmniFocus2LibraryTree, OmniFocus2DescendantTree, OmniFocus2AncestorTree, OmniFocus2Leaf, OmniFocus2FollowingSibling, OmniFocus2PrecedingSibling, OmniFocus2SelectedTree, OmniFocus2Style, OmniFocus2Attribute, OmniFocus2NamedStyle, OmniFocus2RichText, OmniFocus2Character, OmniFocus2Paragraph, OmniFocus2Word, OmniFocus2AttributeRun, OmniFocus2Attachment, OmniFocus2FileAttachment, OmniFocus2Preference;

enum OmniFocus2SaveOptions {
	OmniFocus2SaveOptionsYes = 'yes ' /* Save the file. */,
	OmniFocus2SaveOptionsNo = 'no  ' /* Do not save the file. */,
	OmniFocus2SaveOptionsAsk = 'ask ' /* Ask the user whether or not to save the file. */
};
typedef enum OmniFocus2SaveOptions OmniFocus2SaveOptions;

enum OmniFocus2PrintingErrorHandling {
	OmniFocus2PrintingErrorHandlingStandard = 'lwst' /* Standard PostScript error handling */,
	OmniFocus2PrintingErrorHandlingDetailed = 'lwdt' /* print a detailed report of PostScript errors */
};
typedef enum OmniFocus2PrintingErrorHandling OmniFocus2PrintingErrorHandling;

enum OmniFocus2ProjectStatus {
	OmniFocus2ProjectStatusActive = 'FCPa' /* Active */,
	OmniFocus2ProjectStatusOnHold = 'FCPh' /* On Hold */,
	OmniFocus2ProjectStatusDone = 'FCPd' /* Done */,
	OmniFocus2ProjectStatusDropped = 'FCPD' /* Dropped */
};
typedef enum OmniFocus2ProjectStatus OmniFocus2ProjectStatus;

enum OmniFocus2IntervalUnit {
	OmniFocus2IntervalUnitMinute = 'FCIM' /* Minutes */,
	OmniFocus2IntervalUnitHour = 'FCIH' /* Hours */,
	OmniFocus2IntervalUnitDay = 'FCId' /* Days */,
	OmniFocus2IntervalUnitWeek = 'FCIw' /* Weeks */,
	OmniFocus2IntervalUnitMonth = 'FCIm' /* Months */,
	OmniFocus2IntervalUnitYear = 'FCIy' /* Years */
};
typedef enum OmniFocus2IntervalUnit OmniFocus2IntervalUnit;

enum OmniFocus2RepetitionMethod {
	OmniFocus2RepetitionMethodFixedRepetition = 'FRmF' /* Repeat on a fixed schedule. */,
	OmniFocus2RepetitionMethodStartAfterCompletion = 'FRmS' /* Start again after completion. */,
	OmniFocus2RepetitionMethodDueAfterCompletion = 'FRmD' /* Due again after completion. */
};
typedef enum OmniFocus2RepetitionMethod OmniFocus2RepetitionMethod;

enum OmniFocus2LocationTrigger {
	OmniFocus2LocationTriggerNotifyWhenArriving = 'Larv' /* notify when arriving at this location */,
	OmniFocus2LocationTriggerNotifyWhenLeaving = 'Llev' /* notify when leaving this location */
};
typedef enum OmniFocus2LocationTrigger OmniFocus2LocationTrigger;

enum OmniFocus2SidebarTab {
	OmniFocus2SidebarTabInboxTab = 'FCT0' /* inbox tab */,
	OmniFocus2SidebarTabProjectsTab = 'FCT1' /* projects tab */,
	OmniFocus2SidebarTabContextsTab = 'FCT2' /* contexts tab */,
	OmniFocus2SidebarTabForecastTab = 'FCT3' /* forecast tab */,
	OmniFocus2SidebarTabFlaggedTab = 'FCT4' /* flagged tab */,
	OmniFocus2SidebarTabReviewTab = 'FCT5' /* review tab */
};
typedef enum OmniFocus2SidebarTab OmniFocus2SidebarTab;

enum OmniFocus2TextAlignment {
	OmniFocus2TextAlignmentLeft = 'OTa0',
	OmniFocus2TextAlignmentRight = 'OTa2',
	OmniFocus2TextAlignmentCenter = 'OTa1',
	OmniFocus2TextAlignmentJustified = 'OTa3',
	OmniFocus2TextAlignmentNatural = 'OTa4'
};
typedef enum OmniFocus2TextAlignment OmniFocus2TextAlignment;



/*
 * Standard Suite
 */

// The application's top-level scripting object.
@interface OmniFocus2Application : SBApplication

- (SBElementArray *) documents;
- (SBElementArray *) windows;

@property (copy, readonly) NSString *name;  // The name of the application.
@property (readonly) BOOL frontmost;  // Is this the active application?
@property (copy, readonly) NSString *version;  // The version number of the application.

- (id) open:(id)x usingCache:(BOOL)usingCache repairInPlace:(BOOL)repairInPlace upgradeInPlace:(BOOL)upgradeInPlace;  // Open one or more documents.
- (void) print:(id)x withProperties:(NSDictionary *)withProperties printDialog:(BOOL)printDialog;  // Print a document.
- (void) quitSaving:(OmniFocus2SaveOptions)saving;  // Quit the application.
- (id) duplicate:(id)x to:(SBObject *)to withProperties:(NSDictionary *)withProperties;  // Copy an object.
- (BOOL) exists:(id)x;  // Verify that an object exists.
- (void) GetURL:(NSString *)x;  // Open a document from an URL.
- (NSArray *) complete:(NSString *)x as:(NSNumber *)as spanClass:(NSString *)spanClass maximumMatches:(NSInteger)maximumMatches;  // Generate a list of completions given a string.
- (void) pbcopyItems:(id)items from:(OmniFocus2Tree *)from as:(id)as to:(NSString *)to;  // Copies one or more nodes to the pasteboard.
- (void) pbpasteAt:(SBObject *)at from:(NSString *)from;  // Pastes nodes from the pasteboard.
- (void) pbsaveIn:(NSURL *)in_ as:(NSString *)as from:(NSString *)from;  // Saves data from the pasteboard to a file.
- (void) insert:(NSString *)x at:(SBObject *)at using:(OmniFocus2Style *)using_;  // Insert text in the middle of an existing blob of text.
- (void) add:(id)x to:(SBObject *)to;  // Add the given object(s) to the container.
- (void) remove:(id)x from:(SBObject *)from;  // Remove the given object(s) from the container.

@end

// A document.
@interface OmniFocus2Document : SBObject

@property (copy, readonly) NSString *name;  // Its name.
@property (readonly) BOOL modified;  // Has it been modified since the last save?
@property (copy, readonly) NSURL *file;  // Its location on disk, if it has one.

- (void) closeSaving:(OmniFocus2SaveOptions)saving savingIn:(NSURL *)savingIn;  // Close a document.
- (void) saveIn:(NSURL *)in_ as:(NSString *)as compression:(BOOL)compression;  // Save a document.
- (void) printWithProperties:(NSDictionary *)withProperties printDialog:(BOOL)printDialog;  // Print a document.
- (void) delete;  // Delete an object.
- (id) duplicateTo:(SBObject *)to withProperties:(NSDictionary *)withProperties;  // Copy an object.
- (SBObject *) moveTo:(SBObject *)to;  // Move an object to a new location.
- (SBObject *) archiveIn:(NSURL *)in_ compression:(BOOL)compression summaries:(BOOL)summaries usingCache:(BOOL)usingCache;  // Write an backup archive of the document.
- (void) compact;  // Hides completed tasks and processes any inbox items that have the necessary information into projects and tasks.
- (NSArray *) parseTasksIntoWithTransportText:(NSString *)withTransportText asSingleTask:(BOOL)asSingleTask;  // Converts a textual representation of tasks into tasks.
- (void) undo;  // Undo the last command.
- (void) redo;  // Redo the last undone command.
- (void) synchronize;  // Synchronizes with the shared OmniFocus sync database.
- (void) importIntoFrom:(NSURL *)from at:(SBObject *)at withContextsAt:(SBObject *)withContextsAt;  // Imports a file into an existing OmniFocus document.
- (void) addTo:(SBObject *)to;  // Add the given object(s) to the container.
- (void) removeFrom:(SBObject *)from;  // Remove the given object(s) from the container.

@end

// A window.
@interface OmniFocus2Window : SBObject

@property (copy, readonly) NSString *name;  // The title of the window.
- (NSInteger) id;  // The unique identifier of the window.
@property NSInteger index;  // The index of the window, ordered front to back.
@property NSRect bounds;  // The bounding rectangle of the window.
@property (readonly) BOOL closeable;  // Does the window have a close button?
@property (readonly) BOOL miniaturizable;  // Does the window have a minimize button?
@property BOOL miniaturized;  // Is the window minimized right now?
@property (readonly) BOOL resizable;  // Can the window be resized?
@property BOOL visible;  // Is the window visible right now?
@property (readonly) BOOL zoomable;  // Does the window have a zoom button?
@property BOOL zoomed;  // Is the window zoomed right now?
@property (copy, readonly) OmniFocus2Document *document;  // The document whose contents are displayed in the window.

- (void) closeSaving:(OmniFocus2SaveOptions)saving savingIn:(NSURL *)savingIn;  // Close a document.
- (void) saveIn:(NSURL *)in_ as:(NSString *)as compression:(BOOL)compression;  // Save a document.
- (void) printWithProperties:(NSDictionary *)withProperties printDialog:(BOOL)printDialog;  // Print a document.
- (void) delete;  // Delete an object.
- (id) duplicateTo:(SBObject *)to withProperties:(NSDictionary *)withProperties;  // Copy an object.
- (SBObject *) moveTo:(SBObject *)to;  // Move an object to a new location.
- (SBObject *) archiveIn:(NSURL *)in_ compression:(BOOL)compression summaries:(BOOL)summaries usingCache:(BOOL)usingCache;  // Write an backup archive of the document.
- (void) compact;  // Hides completed tasks and processes any inbox items that have the necessary information into projects and tasks.
- (void) undo;  // Undo the last command.
- (void) redo;  // Redo the last undone command.
- (void) synchronize;  // Synchronizes with the shared OmniFocus sync database.
- (void) addTo:(SBObject *)to;  // Add the given object(s) to the container.
- (void) removeFrom:(SBObject *)from;  // Remove the given object(s) from the container.

@end



/*
 * OmniFocus suite
 */

@interface OmniFocus2Application (OmniFocusSuite)

- (SBElementArray *) perspectives;
- (SBElementArray *) preferences;

@property (copy, readonly) NSString *buildNumber;  // This is the build number of the application, for example 63.1 or 63.  Major and minor versions are separated by a dot.  So 63.10 comes after 63.1.
@property (copy) NSDate *referenceDate;  // The date on from which the date collated smart groups are based.  When set, the reference date will be rounded to the first instant of the day of the specified date.
@property double currentTimeOffset;  // The current time offset from a reference date. Useful for timing scripts.
@property (copy) OmniFocus2Document *defaultDocument;  // The user's default document.
@property (copy) OmniFocus2QuickEntryTree *quickEntry;  // The Quick Entry panel for the default document.
@property (copy, readonly) NSArray *perspectiveNames;  // The names of all available perspectives.

@end

// An OmniFocus document.
@interface OmniFocus2Document (OmniFocusSuite)

- (SBElementArray *) settings;
- (SBElementArray *) documentWindows;
- (SBElementArray *) sections;
- (SBElementArray *) folders;
- (SBElementArray *) projects;
- (SBElementArray *) contexts;
- (SBElementArray *) inboxTasks;
- (SBElementArray *) tasks;
- (SBElementArray *) flattenedTasks;
- (SBElementArray *) flattenedProjects;
- (SBElementArray *) flattenedFolders;
- (SBElementArray *) flattenedContexts;

- (NSString *) id;  // The document's unique identifier.
@property (readonly) BOOL canUndo;  // Whether the document can undo the most recent command.
@property (readonly) BOOL canRedo;  // Whether the document can redo the most recently undone command.
@property BOOL willAutosave;  // Whether the document will autosave.
@property BOOL compressesTransactions;  // Whether the document will write compressed transactions to disk; defaults to true.
@property BOOL includesSummaries;  // Whether the document will write computed summary information when writing transactions.
@property (readonly) BOOL syncing;  // True if the document is currently syncing, false otherwise.
@property (copy, readonly) NSDate *lastSyncDate;  // Date of the last sync.
@property (copy, readonly) NSString *lastSyncError;  // Error message (if any) for the last sync.
@property (copy) OmniFocus2QuickEntryTree *quickEntry;  // The Quick Entry panel for the document.

@end

// A window of an OmniFocus document.
@interface OmniFocus2DocumentWindow : OmniFocus2Window

@property (copy) NSString *searchTerm;  // The search term in the toolbar.  If there is no search toolbar item, this will return missing value instead of an empty string and setting it will cause an error.
@property (copy) id selectedSidebarTab;  // The selected tab in the sidebar.
@property (copy, readonly) OmniFocus2SidebarTree *sidebar;  // The tree of objects in the window sidebar.
@property (copy, readonly) OmniFocus2ContentTree *content;  // The tree of objects in the main window content.
@property (copy) NSString *perspectiveName;  // The name of a perspective.
@property (copy) id focus;  // A list of the projects and folders forming the project focus of this document window.


@end

// Document setting
@interface OmniFocus2Setting : SBObject

- (NSString *) id;  // The identifier of the setting.
@property (copy) id value;  // The current value of the setting.
@property (copy) id defaultValue;  // The default value of the setting.

- (void) closeSaving:(OmniFocus2SaveOptions)saving savingIn:(NSURL *)savingIn;  // Close a document.
- (void) saveIn:(NSURL *)in_ as:(NSString *)as compression:(BOOL)compression;  // Save a document.
- (void) printWithProperties:(NSDictionary *)withProperties printDialog:(BOOL)printDialog;  // Print a document.
- (void) delete;  // Delete an object.
- (id) duplicateTo:(SBObject *)to withProperties:(NSDictionary *)withProperties;  // Copy an object.
- (SBObject *) moveTo:(SBObject *)to;  // Move an object to a new location.
- (SBObject *) archiveIn:(NSURL *)in_ compression:(BOOL)compression summaries:(BOOL)summaries usingCache:(BOOL)usingCache;  // Write an backup archive of the document.
- (void) compact;  // Hides completed tasks and processes any inbox items that have the necessary information into projects and tasks.
- (void) undo;  // Undo the last command.
- (void) redo;  // Redo the last undone command.
- (void) synchronize;  // Synchronizes with the shared OmniFocus sync database.
- (void) addTo:(SBObject *)to;  // Add the given object(s) to the container.
- (void) removeFrom:(SBObject *)from;  // Remove the given object(s) from the container.

@end

// The current focus of a document window.
@interface OmniFocus2FocusSections : SBObject


- (void) closeSaving:(OmniFocus2SaveOptions)saving savingIn:(NSURL *)savingIn;  // Close a document.
- (void) saveIn:(NSURL *)in_ as:(NSString *)as compression:(BOOL)compression;  // Save a document.
- (void) printWithProperties:(NSDictionary *)withProperties printDialog:(BOOL)printDialog;  // Print a document.
- (void) delete;  // Delete an object.
- (id) duplicateTo:(SBObject *)to withProperties:(NSDictionary *)withProperties;  // Copy an object.
- (SBObject *) moveTo:(SBObject *)to;  // Move an object to a new location.
- (SBObject *) archiveIn:(NSURL *)in_ compression:(BOOL)compression summaries:(BOOL)summaries usingCache:(BOOL)usingCache;  // Write an backup archive of the document.
- (void) compact;  // Hides completed tasks and processes any inbox items that have the necessary information into projects and tasks.
- (void) undo;  // Undo the last command.
- (void) redo;  // Redo the last undone command.
- (void) synchronize;  // Synchronizes with the shared OmniFocus sync database.
- (void) addTo:(SBObject *)to;  // Add the given object(s) to the container.
- (void) removeFrom:(SBObject *)from;  // Remove the given object(s) from the container.

@end

// A portion of a folder or document; either a project or a folder.
@interface OmniFocus2Section : SBObject

- (NSString *) id;  // The identifier of the project or folder.
@property (copy) NSString *name;  // The name of the project or folder.

- (void) closeSaving:(OmniFocus2SaveOptions)saving savingIn:(NSURL *)savingIn;  // Close a document.
- (void) saveIn:(NSURL *)in_ as:(NSString *)as compression:(BOOL)compression;  // Save a document.
- (void) printWithProperties:(NSDictionary *)withProperties printDialog:(BOOL)printDialog;  // Print a document.
- (void) delete;  // Delete an object.
- (id) duplicateTo:(SBObject *)to withProperties:(NSDictionary *)withProperties;  // Copy an object.
- (SBObject *) moveTo:(SBObject *)to;  // Move an object to a new location.
- (SBObject *) archiveIn:(NSURL *)in_ compression:(BOOL)compression summaries:(BOOL)summaries usingCache:(BOOL)usingCache;  // Write an backup archive of the document.
- (void) compact;  // Hides completed tasks and processes any inbox items that have the necessary information into projects and tasks.
- (void) undo;  // Undo the last command.
- (void) redo;  // Redo the last undone command.
- (void) synchronize;  // Synchronizes with the shared OmniFocus sync database.
- (void) addTo:(SBObject *)to;  // Add the given object(s) to the container.
- (void) removeFrom:(SBObject *)from;  // Remove the given object(s) from the container.

@end

// A group of projects and sub-folders representing an folder of responsibility.
@interface OmniFocus2Folder : OmniFocus2Section

- (SBElementArray *) sections;
- (SBElementArray *) folders;
- (SBElementArray *) projects;
- (SBElementArray *) flattenedProjects;
- (SBElementArray *) flattenedFolders;

- (NSString *) id;  // The identifier of the folder.
@property (copy) NSString *name;  // The name of the folder.
@property (copy) OmniFocus2RichText *note;  // The note of the folder.
@property BOOL hidden;  // Set if the folder is currently hidden.
@property (readonly) BOOL effectivelyHidden;  // Set if the folder is currently hidden or any of its container folders are hidden.
@property (copy, readonly) NSDate *creationDate;  // When the folder was created.
@property (copy, readonly) NSDate *modificationDate;  // When the folder was last modified.
@property (copy, readonly) id container;  // The containing folder or document.
@property (copy, readonly) id containingDocument;  // The containing document or quick entry tree of the object.


@end

// A context.
@interface OmniFocus2Context : SBObject

- (SBElementArray *) contexts;
- (SBElementArray *) flattenedContexts;
- (SBElementArray *) tasks;
- (SBElementArray *) availableTasks;
- (SBElementArray *) remainingTasks;

- (NSString *) id;  // The identifier of the context.
- (void) setId: (NSString *) id;
@property (copy) NSString *name;  // The name of the context.
@property (copy) OmniFocus2RichText *note;  // The note of the context.
@property BOOL allowsNextAction;  // If false, tasks assigned to this context will be skipped when determining the next action for a project.
@property BOOL hidden;  // Set if the context is currently hidden.
@property (readonly) BOOL effectivelyHidden;  // Set if the context is currently hidden or any of its container contexts are hidden.
@property (copy, readonly) OmniFocus2Context *container;  // The containing context.
@property (readonly) NSInteger availableTaskCount;  // A count of the number of unblocked and incomplete tasks of this context and all its active descendent contexts.
@property (readonly) NSInteger remainingTaskCount;  // A count of the number of incomplete tasks of this context and all its active descendent contexts.
@property (copy, readonly) id containingDocument;  // The containing document or quick entry tree of the object.
@property (copy) id location;  // The physical location of the context.

- (void) closeSaving:(OmniFocus2SaveOptions)saving savingIn:(NSURL *)savingIn;  // Close a document.
- (void) saveIn:(NSURL *)in_ as:(NSString *)as compression:(BOOL)compression;  // Save a document.
- (void) printWithProperties:(NSDictionary *)withProperties printDialog:(BOOL)printDialog;  // Print a document.
- (void) delete;  // Delete an object.
- (id) duplicateTo:(SBObject *)to withProperties:(NSDictionary *)withProperties;  // Copy an object.
- (SBObject *) moveTo:(SBObject *)to;  // Move an object to a new location.
- (SBObject *) archiveIn:(NSURL *)in_ compression:(BOOL)compression summaries:(BOOL)summaries usingCache:(BOOL)usingCache;  // Write an backup archive of the document.
- (void) compact;  // Hides completed tasks and processes any inbox items that have the necessary information into projects and tasks.
- (void) undo;  // Undo the last command.
- (void) redo;  // Redo the last undone command.
- (void) synchronize;  // Synchronizes with the shared OmniFocus sync database.
- (void) addTo:(SBObject *)to;  // Add the given object(s) to the container.
- (void) removeFrom:(SBObject *)from;  // Remove the given object(s) from the container.

@end

// A project.
@interface OmniFocus2Project : OmniFocus2Section

- (NSString *) id;  // The identifier of the project.
- (void) setId: (NSString *) id;
@property (copy, readonly) OmniFocus2Task *rootTask;  // The root task of this project, holding the project's name, note, dates and child tasks.
@property (copy, readonly) id nextTask;  // The next actionable child of this project.
@property (copy) NSDate *lastReviewDate;  // When the project was last reviewed.
@property (copy) NSDate *nextReviewDate;  // When the project should next be reviewed.
@property (copy) NSDictionary *reviewInterval;  // The review interval for the project.
@property OmniFocus2ProjectStatus status;  // The status of the project.
@property BOOL singletonActionHolder;  // True if the project contains singleton actions.
@property BOOL defaultSingletonActionHolder;  // True if the project is the default holder of sington actions.  Only one project can have this flag set; setting it on a project will clear it on any other project having it.  Setting this to true will set 'singleton action holder' to true if not already so set.
@property (copy, readonly) id container;  // The containing folder or document.
@property (copy, readonly) id folder;  // The folder of the project, or missing value if it is contained directly by the document.
@property (copy) NSString *name;  // The name of the project.
@property (copy) OmniFocus2RichText *note;  // The note of the project.
@property (copy, readonly) id containingDocument;  // The containing document or quick entry tree of the object.
@property (copy) id context;  // The project's context.  If a child is added, this will be used for its context.
@property BOOL completedByChildren;  // If true, complete when children are completed.
@property BOOL sequential;  // If true, any children are sequentially dependent.
@property BOOL flagged;  // True if flagged
@property (readonly) BOOL blocked;  // True if the project has a project that must be completed prior to it being actionable.
@property (copy) NSDate *creationDate;  // When the project was created.  This can only be set when the object is still in the inserted state.  For objects created in the document, it can be passed with the creation properties.  For objects in a quick entry tree, it can be set until the quick entry panel is saved.
@property (copy, readonly) NSDate *modificationDate;  // When the project was last modified.
@property (copy) id deferDate;  // When the project should become available for action.
@property (copy) id dueDate;  // When the project must be finished.
@property (copy) id completionDate;  // The project's date of completion.
@property BOOL completed;  // True if the project is completed.
@property (copy) id estimatedMinutes;  // The estimated time, in whole minutes, that this project will take to finish.
@property (copy) id repetitionRule;  // The repetition rule for this project, or missing value if it does not repeat.
@property (readonly) NSInteger numberOfTasks;  // The number of direct children of this project.
@property (readonly) NSInteger numberOfAvailableTasks;  // The number of available direct children of this project.
@property (readonly) NSInteger numberOfCompletedTasks;  // The number of completed direct children of this project.


@end

// A task. This might represent the root of a project, an action within a project or other action or an inbox item.
@interface OmniFocus2Task : SBObject

- (SBElementArray *) tasks;
- (SBElementArray *) flattenedTasks;

- (NSString *) id;  // The identifier of the task.
- (void) setId: (NSString *) id;
@property (copy) NSString *name;  // The name of the task.
@property (copy) OmniFocus2RichText *note;  // The note of the task.
@property (copy, readonly) id container;  // The containing task, project or document.
@property (copy, readonly) id containingProject;  // The task's project, up however many levels of parent tasks.  Inbox tasks aren't considered contained by their provisionalliy assigned container, so if the task is actually an inbox task, this will be missing value.
@property (copy, readonly) id parentTask;  // The task holding this task.  If this is missing value, then this is a top level task -- either the root of a project or an inbox item.
@property (copy, readonly) id containingDocument;  // The containing document or quick entry tree of the object.
@property (readonly) BOOL inInbox;  // Returns true if the task itself is an inbox task or if the task is contained by an inbox task.
@property (copy) id context;  // The task's context.  If a child is added, this will be used for its context.
@property BOOL completedByChildren;  // If true, complete when children are completed.
@property BOOL sequential;  // If true, any children are sequentially dependent.
@property BOOL flagged;  // True if flagged
@property (readonly) BOOL next;  // If the task is the next task of its containing project, next is true.
@property (readonly) BOOL blocked;  // True if the task has a task that must be completed prior to it being actionable.
@property (copy) NSDate *creationDate;  // When the task was created.  This can only be set when the object is still in the inserted state.  For objects created in the document, it can be passed with the creation properties.  For objects in a quick entry tree, it can be set until the quick entry panel is saved.
@property (copy, readonly) NSDate *modificationDate;  // When the task was last modified.
@property (copy) id deferDate;  // When the task should become available for action.
@property (copy) id dueDate;  // When the task must be finished.
@property (copy) id completionDate;  // The task's date of completion.
@property BOOL completed;  // True if the task is completed.
@property (copy) id estimatedMinutes;  // The estimated time, in whole minutes, that this task will take to finish.
@property (copy) id repetitionRule;  // The repetition rule for this task, or missing value if it does not repeat.
@property (readonly) NSInteger numberOfTasks;  // The number of direct children of this task.
@property (readonly) NSInteger numberOfAvailableTasks;  // The number of available direct children of this task.
@property (readonly) NSInteger numberOfCompletedTasks;  // The number of completed direct children of this task.

- (void) closeSaving:(OmniFocus2SaveOptions)saving savingIn:(NSURL *)savingIn;  // Close a document.
- (void) saveIn:(NSURL *)in_ as:(NSString *)as compression:(BOOL)compression;  // Save a document.
- (void) printWithProperties:(NSDictionary *)withProperties printDialog:(BOOL)printDialog;  // Print a document.
- (void) delete;  // Delete an object.
- (id) duplicateTo:(SBObject *)to withProperties:(NSDictionary *)withProperties;  // Copy an object.
- (SBObject *) moveTo:(SBObject *)to;  // Move an object to a new location.
- (SBObject *) archiveIn:(NSURL *)in_ compression:(BOOL)compression summaries:(BOOL)summaries usingCache:(BOOL)usingCache;  // Write an backup archive of the document.
- (void) compact;  // Hides completed tasks and processes any inbox items that have the necessary information into projects and tasks.
- (void) undo;  // Undo the last command.
- (void) redo;  // Redo the last undone command.
- (void) synchronize;  // Synchronizes with the shared OmniFocus sync database.
- (void) addTo:(SBObject *)to;  // Add the given object(s) to the container.
- (void) removeFrom:(SBObject *)from;  // Remove the given object(s) from the container.

@end

// A task that is available for action.  This is simply a filter on the existing tasks and should be considred a read-only element.  These cannot be created directly; instead create a normal task.
@interface OmniFocus2AvailableTask : OmniFocus2Task


@end

// A task that is not complete, though it may be blocked.  This is simply a filter on the existing tasks and should be considred a read-only element.  These cannot be created directly; instead create a normal task.
@interface OmniFocus2RemainingTask : OmniFocus2Task


@end

// A task that is in the document's inbox
@interface OmniFocus2InboxTask : OmniFocus2Task

@property (copy) id assignedContainer;  // Inbox tasks (those contained directly by the document) have a provisionally set container that is made final by the 'compact' command.  This allows you to set and get said container.  The container must be either a task (not in the inbox or contained by an inbox task), a project or 'missing value'.


@end

// A flattened list of tasks under a task or document.
@interface OmniFocus2FlattenedTask : OmniFocus2Task


@end

// A flattened list of projects under a folder or document.
@interface OmniFocus2FlattenedProject : OmniFocus2Project


@end

// A flattened list of folders in a document.
@interface OmniFocus2FlattenedFolder : OmniFocus2Folder


@end

// A flattened list of contexts in a document.
@interface OmniFocus2FlattenedContext : OmniFocus2Context


@end

// A perspective.
@interface OmniFocus2Perspective : SBObject

- (NSString *) id;  // The identifier of the perspective.
- (void) setId: (NSString *) id;
@property (copy) NSString *name;  // The name of the perspective.

- (void) closeSaving:(OmniFocus2SaveOptions)saving savingIn:(NSURL *)savingIn;  // Close a document.
- (void) saveIn:(NSURL *)in_ as:(NSString *)as compression:(BOOL)compression;  // Save a document.
- (void) printWithProperties:(NSDictionary *)withProperties printDialog:(BOOL)printDialog;  // Print a document.
- (void) delete;  // Delete an object.
- (id) duplicateTo:(SBObject *)to withProperties:(NSDictionary *)withProperties;  // Copy an object.
- (SBObject *) moveTo:(SBObject *)to;  // Move an object to a new location.
- (SBObject *) archiveIn:(NSURL *)in_ compression:(BOOL)compression summaries:(BOOL)summaries usingCache:(BOOL)usingCache;  // Write an backup archive of the document.
- (void) compact;  // Hides completed tasks and processes any inbox items that have the necessary information into projects and tasks.
- (void) undo;  // Undo the last command.
- (void) redo;  // Redo the last undone command.
- (void) synchronize;  // Synchronizes with the shared OmniFocus sync database.
- (void) addTo:(SBObject *)to;  // Add the given object(s) to the container.
- (void) removeFrom:(SBObject *)from;  // Remove the given object(s) from the container.

@end



/*
 * Omni Tree Suite
 */

// A tree representing an object, along with its sub-trees.
@interface OmniFocus2Tree : SBObject

- (SBElementArray *) trees;
- (SBElementArray *) descendantTrees;
- (SBElementArray *) ancestorTrees;
- (SBElementArray *) leaves;
- (SBElementArray *) precedingSiblings;
- (SBElementArray *) followingSiblings;
- (SBElementArray *) selectedTrees;

@property (copy, readonly) NSString *name;  // The name of the object being represented by this tree.
- (NSString *) id;  // The identifier of object being represented by this tree.
@property (copy, readonly) id value;  // The object being represented by this tree.
@property BOOL selected;  // This is true if the node is selected.  Note that attempts to set this while the node is not visible (collapsed parent, etc.) will silently do nothing.
@property BOOL expanded;  // This is true if the node is expanded.
@property BOOL noteExpanded;  // This is true if the node note is expanded.
@property (copy) NSArray *writablePasteboardTypes;  // A list of the types that can be used when writing nodes to the pasteboard (i.e., copying).
@property (copy) NSArray *readablePasteboardTypes;  // A list of the types that can be used when reading nodes from the pasteboard (i.e., pasteing).

- (void) closeSaving:(OmniFocus2SaveOptions)saving savingIn:(NSURL *)savingIn;  // Close a document.
- (void) saveIn:(NSURL *)in_ as:(NSString *)as compression:(BOOL)compression;  // Save a document.
- (void) printWithProperties:(NSDictionary *)withProperties printDialog:(BOOL)printDialog;  // Print a document.
- (void) delete;  // Delete an object.
- (id) duplicateTo:(SBObject *)to withProperties:(NSDictionary *)withProperties;  // Copy an object.
- (SBObject *) moveTo:(SBObject *)to;  // Move an object to a new location.
- (SBObject *) archiveIn:(NSURL *)in_ compression:(BOOL)compression summaries:(BOOL)summaries usingCache:(BOOL)usingCache;  // Write an backup archive of the document.
- (void) compact;  // Hides completed tasks and processes any inbox items that have the necessary information into projects and tasks.
- (void) undo;  // Undo the last command.
- (void) redo;  // Redo the last undone command.
- (void) synchronize;  // Synchronizes with the shared OmniFocus sync database.
- (void) addTo:(SBObject *)to;  // Add the given object(s) to the container.
- (void) removeFrom:(SBObject *)from;  // Remove the given object(s) from the container.

@end



/*
 * OmniFocus suite
 */

// The Quick Entry panel.
@interface OmniFocus2QuickEntryTree : OmniFocus2Tree

- (SBElementArray *) folders;
- (SBElementArray *) projects;
- (SBElementArray *) contexts;
- (SBElementArray *) inboxTasks;

@property (readonly) BOOL visible;  // Whether the quick entry panel is currently visible.


@end

// The tree of objects in the window sidebar.
@interface OmniFocus2SidebarTree : OmniFocus2Tree



@end

// The tree of objects in the main window content.
@interface OmniFocus2ContentTree : OmniFocus2Tree

@property (copy, readonly) NSArray *availableGroupingIdentifiers;  // The list of possible identifiers that can be set as the selected grouping identifier.
@property (copy) NSString *selectedGroupingIdentifier;  // The currently selected grouping identifier, controlling how the results shown in the content area are grouped.
@property (copy, readonly) NSArray *availableSortingIdentifiers;  // The list of possible identifiers that can be set as the selected sorting identifier.
@property (copy) NSString *selectedSortingIdentifier;  // The currently selected sorting identifier, controlling how the results shown in the content area are ordered.
@property (copy, readonly) NSArray *availableTaskStateFilterIdentifiers;  // The list of possible identifiers that can be set as the selected task state filter identifier.
@property (copy) NSString *selectedTaskStateFilterIdentifier;  // The currently selected task state filter identifier.
@property (copy, readonly) NSArray *availableTaskDurationFilterIdentifiers;  // The list of possible identifiers that can be set as the selected task duration filter identifier.
@property (copy) NSString *selectedTaskDurationFilterIdentifier;  // The currently selected task duration filter identifier.
@property (copy, readonly) NSArray *availableTaskFlaggedFilterIdentifiers;  // The list of possible identifiers that can be set as the selected task flagged filter identifier.
@property (copy) NSString *selectedTaskFlaggedFilterIdentifier;  // The currently selected task flagged filter identifier.


@end

// The tree in the sidebar representing the Inbox.
@interface OmniFocus2InboxTree : OmniFocus2Tree


@end

// The tree in the sidebar representing the top level library of objects.
@interface OmniFocus2LibraryTree : OmniFocus2Tree


@end



/*
 * Omni Tree Suite
 */

// All the descendant trees in the user-specified sort ordering, listing each tree, then its children and so forth.
@interface OmniFocus2DescendantTree : OmniFocus2Tree


@end

// The ancestor trees of this tree.
@interface OmniFocus2AncestorTree : OmniFocus2Tree


@end

// The descendants of a tree that have no children themselves.
@interface OmniFocus2Leaf : OmniFocus2Tree


@end

// The sibling trees of this tree after it in the user-specified sort ordering.
@interface OmniFocus2FollowingSibling : OmniFocus2Tree


@end

// The sibling trees of this tree before it in the user-specified sort ordering.
@interface OmniFocus2PrecedingSibling : OmniFocus2Tree


@end

// The trees of this tree that are selected in the user interface, possibly including this tree.
@interface OmniFocus2SelectedTree : OmniFocus2Tree


@end



/*
 * OmniStyle Scripting
 */

// A style object.
@interface OmniFocus2Style : SBObject

- (SBElementArray *) namedStyles;
- (SBElementArray *) attributes;

@property (copy, readonly) id container;  // The object owning the style.
@property (copy) NSString *font;  // The name of the font of the style.

- (void) closeSaving:(OmniFocus2SaveOptions)saving savingIn:(NSURL *)savingIn;  // Close a document.
- (void) saveIn:(NSURL *)in_ as:(NSString *)as compression:(BOOL)compression;  // Save a document.
- (void) printWithProperties:(NSDictionary *)withProperties printDialog:(BOOL)printDialog;  // Print a document.
- (void) delete;  // Delete an object.
- (id) duplicateTo:(SBObject *)to withProperties:(NSDictionary *)withProperties;  // Copy an object.
- (SBObject *) moveTo:(SBObject *)to;  // Move an object to a new location.
- (SBObject *) archiveIn:(NSURL *)in_ compression:(BOOL)compression summaries:(BOOL)summaries usingCache:(BOOL)usingCache;  // Write an backup archive of the document.
- (void) compact;  // Hides completed tasks and processes any inbox items that have the necessary information into projects and tasks.
- (void) undo;  // Undo the last command.
- (void) redo;  // Redo the last undone command.
- (void) synchronize;  // Synchronizes with the shared OmniFocus sync database.
- (void) addTo:(SBObject *)to;  // Add the given object(s) to the container.
- (void) removeFrom:(SBObject *)from;  // Remove the given object(s) from the container.

@end

// An attribute of a style.
@interface OmniFocus2Attribute : SBObject

@property (copy, readonly) NSString *name;  // The name of the attribute.
@property (copy) OmniFocus2Style *style;  // The style to which the attribute refers.
@property (copy, readonly) OmniFocus2Style *definingStyle;  // The style responsible for the effective value in this attributes's style.  This processes the local values, inherited styles and cascade chain.
@property (copy) id value;  // The value of the attribute in its style.
@property (copy) id defaultValue;  // The default value of the attribute in its style.

- (void) closeSaving:(OmniFocus2SaveOptions)saving savingIn:(NSURL *)savingIn;  // Close a document.
- (void) saveIn:(NSURL *)in_ as:(NSString *)as compression:(BOOL)compression;  // Save a document.
- (void) printWithProperties:(NSDictionary *)withProperties printDialog:(BOOL)printDialog;  // Print a document.
- (void) delete;  // Delete an object.
- (id) duplicateTo:(SBObject *)to withProperties:(NSDictionary *)withProperties;  // Copy an object.
- (SBObject *) moveTo:(SBObject *)to;  // Move an object to a new location.
- (SBObject *) archiveIn:(NSURL *)in_ compression:(BOOL)compression summaries:(BOOL)summaries usingCache:(BOOL)usingCache;  // Write an backup archive of the document.
- (void) compact;  // Hides completed tasks and processes any inbox items that have the necessary information into projects and tasks.
- (void) undo;  // Undo the last command.
- (void) redo;  // Redo the last undone command.
- (void) synchronize;  // Synchronizes with the shared OmniFocus sync database.
- (void) addTo:(SBObject *)to;  // Add the given object(s) to the container.
- (void) removeFrom:(SBObject *)from;  // Remove the given object(s) from the container.

@end

// A named style object.
@interface OmniFocus2NamedStyle : OmniFocus2Style

- (NSString *) id;  // An identifier for the named style that is unique within its document.  Currently this identifier is not persistent between two different sessions of editing the document.
@property (copy) NSString *name;  // The name of the style.  Must be unique within the containing document.


@end



/*
 * Omni Text Suite
 */

// Rich (styled) text
@interface OmniFocus2RichText : SBObject

- (SBElementArray *) characters;
- (SBElementArray *) paragraphs;
- (SBElementArray *) words;
- (SBElementArray *) attributeRuns;
- (SBElementArray *) attachments;
- (SBElementArray *) fileAttachments;

@property (copy) NSString *text;  // The plain text contents of the rich text.
@property (copy) NSColor *color;  // The color of the first character.
@property (copy) NSString *font;  // The name of the font of the first character.
@property NSInteger size;  // The size in points of the first character.
@property (copy) OmniFocus2Style *style;  // The style of the text.

- (void) closeSaving:(OmniFocus2SaveOptions)saving savingIn:(NSURL *)savingIn;  // Close a document.
- (void) saveIn:(NSURL *)in_ as:(NSString *)as compression:(BOOL)compression;  // Save a document.
- (void) printWithProperties:(NSDictionary *)withProperties printDialog:(BOOL)printDialog;  // Print a document.
- (void) delete;  // Delete an object.
- (id) duplicateTo:(SBObject *)to withProperties:(NSDictionary *)withProperties;  // Copy an object.
- (SBObject *) moveTo:(SBObject *)to;  // Move an object to a new location.
- (SBObject *) archiveIn:(NSURL *)in_ compression:(BOOL)compression summaries:(BOOL)summaries usingCache:(BOOL)usingCache;  // Write an backup archive of the document.
- (void) compact;  // Hides completed tasks and processes any inbox items that have the necessary information into projects and tasks.
- (void) undo;  // Undo the last command.
- (void) redo;  // Redo the last undone command.
- (void) synchronize;  // Synchronizes with the shared OmniFocus sync database.
- (void) bold;  // Bold some text
- (void) italicize;  // Italicize some text
- (void) replaceMatchingRegularExpression:(NSString *)matchingRegularExpression replacement:(NSString *)replacement string:(NSString *)string;
- (void) unbold;  // Unbold some text
- (void) underline;  // Underline some text
- (void) unitalicize;  // Unitalicize some text
- (void) ununderline;  // Ununderline some text
- (void) addTo:(SBObject *)to;  // Add the given object(s) to the container.
- (void) removeFrom:(SBObject *)from;  // Remove the given object(s) from the container.

@end

// This subdivides the text into characters.
@interface OmniFocus2Character : OmniFocus2RichText


@end

// This subdivides the text into paragraphs.
@interface OmniFocus2Paragraph : OmniFocus2RichText


@end

// This subdivides the text into words.
@interface OmniFocus2Word : OmniFocus2RichText


@end

// This subdivides the text into chunks that all have the same attributes.
@interface OmniFocus2AttributeRun : OmniFocus2RichText


@end

// Represents an inline text attachment.
@interface OmniFocus2Attachment : OmniFocus2RichText


@end

// A text attachment refering to a plain file.
@interface OmniFocus2FileAttachment : OmniFocus2Attachment

@property (copy, readonly) NSURL *fileName;  // The path to the file for the attachment, if the attachment resides outside the document.
@property (readonly) BOOL embedded;  // If true, the attached file will reside inside the document on the next save.


@end



/*
 * Extended Text Suite
 */

@interface OmniFocus2RichText (ExtendedTextSuite)

@property double baselineOffset;  // Number of pixels shifted above or below the normal baseline.
@property BOOL underlined;  // Is the first character underlined?
@property NSInteger superscript;  // The superscript level of the text.
@property OmniFocus2TextAlignment alignment;  // Alignment of the text.

@end



/*
 * OmniFoundation Scripting
 */

// Application preference
@interface OmniFocus2Preference : SBObject

- (NSString *) id;  // The identifier of the preference.
@property (copy) id value;  // The current value of the preference.
@property (copy) id defaultValue;  // The default value of the preference.

- (void) closeSaving:(OmniFocus2SaveOptions)saving savingIn:(NSURL *)savingIn;  // Close a document.
- (void) saveIn:(NSURL *)in_ as:(NSString *)as compression:(BOOL)compression;  // Save a document.
- (void) printWithProperties:(NSDictionary *)withProperties printDialog:(BOOL)printDialog;  // Print a document.
- (void) delete;  // Delete an object.
- (id) duplicateTo:(SBObject *)to withProperties:(NSDictionary *)withProperties;  // Copy an object.
- (SBObject *) moveTo:(SBObject *)to;  // Move an object to a new location.
- (SBObject *) archiveIn:(NSURL *)in_ compression:(BOOL)compression summaries:(BOOL)summaries usingCache:(BOOL)usingCache;  // Write an backup archive of the document.
- (void) compact;  // Hides completed tasks and processes any inbox items that have the necessary information into projects and tasks.
- (void) undo;  // Undo the last command.
- (void) redo;  // Redo the last undone command.
- (void) synchronize;  // Synchronizes with the shared OmniFocus sync database.
- (void) addTo:(SBObject *)to;  // Add the given object(s) to the container.
- (void) removeFrom:(SBObject *)from;  // Remove the given object(s) from the container.

@end

