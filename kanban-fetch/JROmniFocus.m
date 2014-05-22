//
//  JROmniFocus.m
//  kanban-fetch
//
//  Created by Jan-Yves on 21/11/13.
//  Copyright (c) 2013 Jan-Yves Ruzicka. All rights reserved.
//

#import "JROmniFocus.h"

#import "OmniFocus2.h"
#import "SystemEvents.h"

static OmniFocus2Application* kJROF;
static SBElementArray *kProjects, *kTasks;
static NSString *kOF2ID = @"com.omnigroup.OmniFocus2";

@implementation JROmniFocus

+(OmniFocus2Application *)omnifocus {
    if (!kJROF)
        kJROF = [SBApplication applicationWithBundleIdentifier:kOF2ID];
    
    return kJROF;
}

+(BOOL) isRunning {
    NSArray *apps = [[NSWorkspace sharedWorkspace] runningApplications];
    for (NSRunningApplication *app in apps) {
        if ([app.bundleIdentifier isEqualToString:kOF2ID])
            return true;
    }
    return false;
}

+(SBElementArray *)projects {
    if (!kProjects)
        kProjects = [[[self omnifocus] defaultDocument] flattenedProjects];
    return kProjects;
}

+(SBElementArray *)tasks {
    if (!kTasks)
        kTasks = [[[self omnifocus] defaultDocument] flattenedTasks];
    return kTasks;
}

@end
