//
//  JROmniFocus.m
//  kanban-fetch
//
//  Created by Jan-Yves on 21/11/13.
//  Copyright (c) 2013 Jan-Yves Ruzicka. All rights reserved.
//

#import "JROmniFocus.h"
#import "OmniFocus2.h"

static OmniFocus2Application* kJROF;
static SBElementArray *kProjects, *kTasks;

@implementation JROmniFocus

+(OmniFocus2Application *)omnifocus {
    if (!kJROF)
        kJROF = [SBApplication applicationWithBundleIdentifier:@"com.omnigroup.omnifocus2"];
    
    return kJROF;
}

+(BOOL) isRunning {
    return [[self omnifocus] isRunning];
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
