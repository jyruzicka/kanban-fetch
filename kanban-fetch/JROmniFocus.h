//
//  JROmniFocus.h
//  kanban-fetch
//
//  Created by Jan-Yves on 21/11/13.
//  Copyright (c) 2013 Jan-Yves Ruzicka. All rights reserved.
//

#import <Foundation/Foundation.h>
@class SBElementArray;

@interface JROmniFocus : NSObject

+(BOOL)isRunning;
+(SBElementArray *)projects;
+(SBElementArray *)tasks;
@end
