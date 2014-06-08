//
//  main.m
//  kanban-fetch
//
//  Created by Jan-Yves on 18/11/13.
//  Copyright (c) 2013 Jan-Yves Ruzicka. All rights reserved.
//

#import <Foundation/Foundation.h>

//For output
#import "JRLogger.h"

//Omnifocus stuff
#import "JROmniFocus.h"
#import "JRProject.h"
#import "JRDatabaseManager.h"

//Options
#import <BRLOptionParser/BRLOptionParser.h>

static const NSString *VERSION_NUMBER = @"1.1.4";

int main(int argc, const char * argv[])
{
    @autoreleasepool {
        //Error
        NSError *err;
        
        //BRLOP arguments
        BOOL debug=NO;
        NSString *dbPath;
        NSString *excludeFolders;
        
        
        JRLogger *logger = [JRLogger logger];
        
        // Initialize option parser
        BRLOptionParser *options = [BRLOptionParser new];
        [options setBanner: @"kanban-fetch for OmniFocus 1, Version %@\n\nusage: %s [--debug] [--exclude=\"exclude1,...\"] --out=DATABASE\n       %s --help\n",VERSION_NUMBER,argv[0], argv[0]];
        
        [options addOption:"debug" flag:'d' description:@"Activates debug mode, with appropriate output" value:&debug];
        [options addOption:"out" flag:'o' description:@"Name of database. Required" argument:&dbPath];
        [options addOption:"exclude" flag:'x' description:@"Projects in folders with this name will be excluded from export. Separate folders by commas." argument:&excludeFolders];
        
        
        __weak typeof(options) weakOptions = options;
        [options addOption:"help" flag:'h' description:@"Show this message" block:^{
            [logger log:@"%@",weakOptions.description];
            exit(EXIT_SUCCESS);
        }];
        
        if (![options parseArgc:argc argv:argv error:&err])
            [logger fail:@"%s: %@",argv[0], err.localizedDescription];
        
        if (debug)
            logger.debugging = YES;
        
        // Check for database location
        if (!dbPath) [logger fail: @"Option --out is required."];

        //Quit if OmniFocus isn't running
        if (![JROmniFocus isRunning]) {
            [logger debug:@"Omnifocus isn't running. Quitting..."];
            exit(EXIT_SUCCESS);
        }
                    
        //Determine path to write to
        [logger debug:@"Setting database path to %@", dbPath];
        JRDatabaseManager.databasePath = dbPath;
        
        //Determine folder exclusion
        if (excludeFolders) {
            [logger debug:@"Excluding folders: %@",excludeFolders];
            [JRProject excludeFolders:[excludeFolders componentsSeparatedByString:@","]];
        }
        
        // Fetch *all* current projects
        SBElementArray *allProjects = [JROmniFocus projects];
        [logger debug:@"Fetched %lu projects from OmniFocus.", [allProjects count]];
        NSMutableArray *kbProjects = [NSMutableArray arrayWithCapacity:[allProjects count]];
    
        for (OmniFocusProject *p in allProjects) {
            JRProject *kbp = [JRProject projectWithProject:p];
            if ([kbp isReportable])
                [kbProjects addObject: kbp];
        }
        [logger debug:@"Generated %lu reportable projects.", [kbProjects count]];
        
        // Now save
        err = [JRDatabaseManager purgeDatabase];
        if (err) {
            [logger error:@"Error while purging database:"];
            [logger error:@"%@",err.localizedDescription];
            [JRDatabaseManager close];
            exit(EXIT_FAILURE);
        }
        
        for (JRProject *p in kbProjects) {
            [logger debug:@"  Writing project: %@",p.name];
            err = [JRDatabaseManager writeProject:p];
            if (err) break;
        }
        
        if (err) {
            [logger error:@"Error while writing projects:"];
            [logger error:@"%@", err.localizedDescription];
            [JRDatabaseManager close];
            exit(EXIT_FAILURE);
        }
        [logger debug:@"Closing database connection..."];
        [JRDatabaseManager close];
        [logger debug:@"Success! Ending..."];
    }
    exit(EXIT_SUCCESS);
}

