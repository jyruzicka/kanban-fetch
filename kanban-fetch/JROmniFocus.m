//
//  JROmniFocus.m
//  kanban-fetch
//
//  Created by Jan-Yves on 21/11/13.
//  Copyright (c) 2013 Jan-Yves Ruzicka. All rights reserved.
//

#import "JROmniFocus.h"

#import "OmniFocus.h"
#import "SystemEvents.h"

#import "JRLogger.h"

static OmniFocusApplication* kJROF;
static SBElementArray *kProjects, *kTasks;
static NSString *kOF2ID = @"com.omnigroup.OmniFocus2";
static NSString *kOF2AppStoreID = @"com.omnigroup.OmniFocus2.MacAppStore";
NSString *kJRAppIdentifier;

@implementation JROmniFocus

+(BOOL) isRunning {
    NSArray *apps = [[NSWorkspace sharedWorkspace] runningApplications];
    for (NSRunningApplication *app in apps) {
        if ([app.bundleIdentifier isEqualToString:kOF2ID] ||
            [app.bundleIdentifier isEqualToString:kOF2AppStoreID]) {
            
            kJRAppIdentifier = app.bundleIdentifier;
            [[JRLogger logger] debug:@"OmniFocus bundle identified: %@",kJRAppIdentifier];
            return true;
        }
    }
    return false;
}

+(BOOL) isPro {
    @try {
        [[self omnifocus] defaultDocument];
        return YES;
    }
    @catch (NSException *exception) {
        return NO;
    }
}

+(OmniFocusApplication *)omnifocus {
    if (!kJROF){
        [[JRLogger logger] debug:@"Connection to bundle: %@",kJRAppIdentifier];
        kJROF = [SBApplication applicationWithBundleIdentifier:kJRAppIdentifier];
    }
    return kJROF;
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
