//
//  JRDatabaseManager.h
//  kanban-fetch
//
//  Created by Jan-Yves on 19/11/13.
//  Copyright (c) 2013 Jan-Yves Ruzicka. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FMDatabase.h>

@class JRProject;

@interface JRDatabaseManager : NSObject

#pragma mark DB accessor method
+(FMDatabase *)database;

#pragma mark DB path
+(NSString *)databasePath;
+(void)setDatabasePath:(NSString *)path;

#pragma mark - Database helpers
+(NSError *)writeProjects:(NSArray *)projects;
+(NSError *)writeProject:(JRProject *)project;
+(NSError *)purgeDatabase;
+(void)close;

@end
