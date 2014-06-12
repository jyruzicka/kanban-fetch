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
#import <JROFBridge/JROmniFocus.h>
#import <JROFBridge/JRProject.h>
#import <JROFBridge/JRDatabase.h>

//Options
#import <BRLOptionParser/BRLOptionParser.h>

static const NSString *VERSION_NUMBER = @"2.1.1";

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
        
        //------------------------------------------------------------------------------
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
        JROmniFocus *of = [JROmniFocus instance];
        if (!of) {
            [logger debug:@"Omnifocus isn't running. Quitting..."];
            exit(EXIT_SUCCESS);
        }
        
        if (debug) {
            NSString *vers;
            switch(of.version) {
                case JROmniFocusVersion1:
                    vers = @"1";
                    break;
                case JROmniFocusVersion2:
                    vers = @"2 Standard";
                    break;
                default:
                    vers = @"2 Pro";
            }
            	
            [logger debug: @"OmniFocus version detected: OmniFocus %@",vers];
        }
        
        //Quit if not pro
        if (!of.version == JROmniFocusVersion2) [logger fail:@"You appear to be using OmniFocus 2 Standard. kanban-fetch will only work with OmniFocus 2 Pro. If you have just purchased OmniFocus Pro, try restarting OmniFocus.\nSorry for the inconvenience!"];
        
        //Determine path to write to
        [logger debug:@"Setting database path to %@", dbPath];
        JRDatabase *db = [JRDatabase databaseWithLocation:dbPath type:JRDatabaseProjects];
        
        if (!db.canExist)
            [logger fail:@"Cannot create database at location: %@",dbPath];
        
        //Determine folder exclusion
        if (excludeFolders) {
            [logger debug:@"Excluding folders: %@",excludeFolders];
            of.excludedFolders = [excludeFolders componentsSeparatedByString:@","];
        }
        
        // Fetch completed projects
        NSMutableArray *projects = [NSMutableArray array];
        [of eachProject:^(JRProject *p){ if (![p.ancestry isEqualToString:@""]) [projects addObject:p]; }];
        [logger debug:@"Generated %lu reportable projects.", projects.count];
        
        // Now save
        [logger debug:@"Purging and recreating database as required..."];
        err = [db purgeDatabase];
        if (err) {
            [logger error:@"Error while purging database:"];
            [logger error:@"%@",err.localizedDescription];
            exit(EXIT_FAILURE);
        }
        
        [logger debug:@"Writing projects:"];
        for (JRProject *p in projects) {
            [logger debug:@"  Writing project: %@",p.name];
            err = [db saveProject:p];
            if (err) break;
        }
        
        if (err) {
            [logger error:@"Error while writing projects:"];
            [logger error:@"%@", err.localizedDescription];
            exit(EXIT_FAILURE);
        }
        [logger debug:@"Success!"];
    }
    exit(EXIT_SUCCESS);
}

