//
//  JRDatabaseManager.m
//  kanban-fetch
//
//  Created by Jan-Yves on 19/11/13.
//  Copyright (c) 2013 Jan-Yves Ruzicka. All rights reserved.
//

#import "JRDatabaseManager.h"
#import "JRProject.h"
#import <FMDatabaseAdditions.h>

static FMDatabase *kJRDatabase;
static NSString *kJRDatabasePath;

@implementation JRDatabaseManager

#pragma mark Ensure DB exists
+(FMDatabase *)database {
    if (!kJRDatabase) {
        NSString *dbPath = [JRDatabaseManager databasePath];
        if (dbPath) {
            
        NSFileManager *fm = [NSFileManager defaultManager];
        BOOL newDB = (![fm fileExistsAtPath:dbPath]);
        
        kJRDatabase = [FMDatabase databaseWithPath:dbPath];
        [kJRDatabase open];
        
        if (newDB)
            [kJRDatabase update:@"CREATE TABLE projects (id INTEGER PRIMARY KEY, name STRING, ofid STRING, status STRING, ancestors STRING, num_tasks INTEGER, daysdeferred INTEGER);" withErrorAndBindings:nil];
        }
    }
    return kJRDatabase;
}

#pragma mark Database path methods
+(NSString *)databasePath {
    return kJRDatabasePath;
}

+(void)setDatabasePath:(NSString *)path {
    kJRDatabasePath = path.stringByExpandingTildeInPath;
}
     
+(NSError *)writeProject:(JRProject *)p {
    FMDatabase *db = [self database];
    NSError *rErr;
    
    NSUInteger rows = [db intForQuery:@"SELECT COUNT(*) FROM projects WHERE ofid=?",[p id]];
    if (rows > 0) {// Project already exists! Update
        if (![db
                executeUpdate:@"UPDATE projects SET name=:name, status=:status, ancestors=:ancestors, daysdeferred=:daysdeferred,num_tasks=:numtasks WHERE ofid=:ofid"
                withParameterDictionary:[p dict]])
            rErr = [db lastError];
    }
    else {
         if (![db
                executeUpdate:@"INSERT INTO projects (name,status,ancestors,daysdeferred,num_tasks,ofid) VALUES (:name, :status, :ancestors, :daysdeferred, :numtasks, :ofid)"
                withParameterDictionary:[p dict]])
             rErr = [db lastError];
    }
    
    return  rErr;
}

+(NSError *)purgeDatabase {
    NSError *rErr;
    FMDatabase *db = [self database];
    [db update:@"DELETE FROM projects" withErrorAndBindings:&rErr];
    return rErr;
}

+(void) close {
    [[self database] close];
}
@end
