#import "JRProject.h"
#import "JROmniFocus.h"

//For exlcluded folders
NSArray *excludedFolders;

@implementation JRProject

-(id)initWithProject:(OmniFocus2Project *)proj {
  if (self = [super init]) {
    p = proj;
  }
  return self;
}

+(id)projectWithProject:(OmniFocus2Project *)proj {
  return [[self alloc] initWithProject:proj];
}

#pragma mark - Special fetcher methods
-(int)daysDeferred {
  if (!_daysDeferred) {
    if ([self type] == kJRDeferredProject) {
        NSDate *start = [[p deferDate] get];
         //No start date on project, or start date is in the past
        if (!start || [start timeIntervalSinceNow] < 0)
            start = [[[self tasks][0] deferDate] get];
        
        NSTimeInterval i = [start timeIntervalSinceNow];
        _daysDeferred = i / (60 * 60 * 24);
    }
    else _daysDeferred = -1;
  }
  return _daysDeferred;
}

-(JRProjectStatus)type {
  if (!_type) {
    if ([self isCompleted])
      _type = kJRCompletedProject;
    else if ([self isDropped])
      _type = kJRCompletedProject;
    else if ([self isOnHold])
      _type = kJRBackburnerProject;
    else if ([[self tasks] count] == 0)
      _type = kJRHangingProject;
    else if ([[self availableTasks] count] == 0)
      _type = kJRDeferredProject;
    else if ([self isWaiting])
      _type = kJRWaitingOnProject;
    else
      _type = kJRActiveProject;
  }
  return _type;
}

-(NSString *)stringType {
    switch ([self type]) {
        case kJRCompletedProject:
            return @"Completed";
        case kJRBackburnerProject:
            return @"Backburner";
        case kJRHangingProject:
            return @"Hanging";
        case kJRDeferredProject:
            return @"Deferred";
        case kJRWaitingOnProject:
            return @"Waiting on";
        case kJRActiveProject:
            return @"Active";
    }
    return nil;
}

#pragma mark - Name and data methods

-(NSString *)name {return p.name;}
-(NSString *)id {return p.id;}
-(BOOL)isCompleted {return p.completed;}

-(BOOL)isDropped {
  return (p.status == OmniFocus2ProjectStatusDropped);
}

-(BOOL)isOnHold {
  return (p.status == OmniFocus2ProjectStatusOnHold);
}

-(BOOL)isWaiting {
    for (OmniFocus2Task *t in [self availableTasks])
        if (![[[t.context get] name] isEqualToString:@"Waiting for..."])
            return NO;
    
    return YES;
}

#pragma mark - Tasks
-(NSArray *)tasks {
    if (!_tasks) {
        NSPredicate *pred = [NSPredicate predicateWithFormat:@"completed = FALSE"];
        _tasks = [[[p rootTask] flattenedTasks] filteredArrayUsingPredicate:pred];
    }

    return _tasks;
}

-(NSArray *)availableTasks {
    if (!_availableTasks) {
        NSPredicate *pred = [NSPredicate predicateWithFormat:@"blocked = FALSE"];
        _availableTasks = [[self tasks] filteredArrayUsingPredicate:pred];
    }
    return _availableTasks;
}

-(NSUInteger)numberOfTasks {
    return [[self tasks] count];
}

#pragma mark - Ancestors
-(NSArray *)ancestors {
    if (!_ancestors) {
        _ancestors = [NSMutableArray array];
        id marker = [[p container] get];
        while (![[marker className] isEqualToString:@"OmniFocusDocument"]) {
            [_ancestors insertObject:[marker name] atIndex:0];
            marker = [[marker container] get];
        }
    }
    return _ancestors;
}

-(NSString *)ancestorsString {
    if ([[self ancestors] count] == 0)
        return @"";
    else
        return [[self ancestors] componentsJoinedByString:@"|"];
}

-(NSString *)root {
    if ([[self ancestors] count] == 0)
        return nil;
    else
        return [self ancestors][0];
}

-(BOOL)isReportable {
    if (!self.root) return NO;
    
    if (excludedFolders)
        for (NSString *exclFolder in excludedFolders)
                if ([self.root isEqualToString:exclFolder]) return NO;
    
    return YES;
}

#pragma mark - Serialization

-(NSDictionary *)dict {
    return @{
    @"name":        [self name],
    @"ofid":        [self id],
    @"status":      [self stringType],
    @"ancestors":   [self ancestorsString],
    @"daysdeferred":[NSNumber numberWithInt:[self daysDeferred]],
    @"numtasks":    [NSNumber numberWithUnsignedLong:[self numberOfTasks]]
    };
}

#pragma mark - Manage exclued folders
+(void)excludeFolders:(NSArray *)folders {
    excludedFolders = folders;
}
@end