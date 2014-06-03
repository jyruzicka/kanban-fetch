#import <Cocoa/Cocoa.h>
#import "OmniFocus2.h"

@class OmniFocus2Project;

typedef enum {
    kJRActiveProject,
    kJRCompletedProject,
    kJRBackburnerProject,
    kJRHangingProject,
    kJRDeferredProject,
    kJRWaitingOnProject
} JRProjectStatus;

@interface JRProject : NSObject {
    OmniFocus2Project *p;
    int _daysDeferred;
    JRProjectStatus _type;
    NSArray *_availableTasks, *_tasks;
    NSMutableArray *_ancestors;
}

-(id)initWithProject:(OmniFocus2Project *)proj;
+(id)projectWithProject:(OmniFocus2Project *)proj;

#pragma mark - Pseudoproperties
-(int)daysDeferred;
-(JRProjectStatus)type;
-(NSString *)stringType;

#pragma mark - Extensions of project
-(NSString *)name;
-(NSString *)id;
-(BOOL)isCompleted;
-(BOOL)isDropped;
-(BOOL)isOnHold;
-(BOOL)isWaiting;

#pragma mark - Tasks
-(NSArray *)tasks;
-(NSArray *)availableTasks;
-(NSUInteger)numberOfTasks;

#pragma mark - Ancestors
-(NSArray *)ancestors;
-(NSString *)ancestorsString;
-(NSString *)root;
-(BOOL)isReportable;

#pragma mark - For serialization
-(NSDictionary *)dict;

#pragma mark - Manage exclued folders
+(void)excludeFolders:(NSArray *)folders;

@end