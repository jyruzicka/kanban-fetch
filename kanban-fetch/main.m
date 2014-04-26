//
//  main.m
//  kanban-fetch
//
//  Created by Jan-Yves on 18/11/13.
//  Copyright (c) 2013 Jan-Yves Ruzicka. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JROmniFocus.h"
#import "JRProject.h"
#import "JRDatabaseManager.h"

int main(int argc, const char * argv[])
{

    @autoreleasepool {
        NSError *err;
        if (argc != 2) {
            printf("Usage:\n  kanban-fetch DBPATH\n");
            return 1;
        }

        //Quit if OmniFocus isn't running
        if (![JROmniFocus isRunning])
            return 0;
            
        //Determine path to write to
        NSString *path = [NSString stringWithCString:argv[1] encoding:NSUTF8StringEncoding];
        path = path.stringByExpandingTildeInPath;
        [JRDatabaseManager setDatabasePath:path];
        
        // Fetch *all* current projects
        SBElementArray *allProjects = [JROmniFocus projects];
        NSMutableArray *kbProjects = [NSMutableArray arrayWithCapacity:[allProjects count]];
    
        for (OmniFocus2Project *p in allProjects) {
            JRProject *kbp = [JRProject projectWithProject:p];
            if ([kbp isReportable])
                [kbProjects addObject: kbp];
        }
        
        // Now save
        err = [JRDatabaseManager purgeDatabase];
        if (err) {
            printf("Error while purging database:\n");
            printf("%s\n",[err.localizedDescription cStringUsingEncoding:NSUTF8StringEncoding]);
            [JRDatabaseManager close];
            return 1;
        }
        
        err = [JRDatabaseManager writeProjects:kbProjects];
        if (err) {
            printf("Error while writing projects:\n");
            printf("%s\n", [err.localizedDescription cStringUsingEncoding:NSUTF8StringEncoding]);
            [JRDatabaseManager close];
            return 1;
        }
        [JRDatabaseManager close];
    }
    return 0;
}

