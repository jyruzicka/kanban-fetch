//
//  JRLogger.m
//  kanban-fetch
//
//  Created by Jan-Yves on 27/05/14.
//  Copyright (c) 2014 Jan-Yves Ruzicka. All rights reserved.
//

#import "JRLogger.h"

@implementation JRLogger

-(void)log:(NSString *)str, ... {
    va_list args;
    va_start(args,str);
    NSString *newStr = [[NSString alloc] initWithFormat:str arguments:args];
    va_end(args);

    [self writeToLocation:@"/dev/stdout" withString:newStr];
}

-(void)error:(NSString *)str,... {
    va_list args;
    va_start(args,str);
    NSString *newStr = [[NSString alloc] initWithFormat:str arguments:args];
    va_end(args);
    [self writeToLocation:@"/dev/stderr" withString:newStr];
}

-(void)debug:(NSString *)str, ... {
    if (self.debugging) {
        va_list args;
        va_start(args,str);
        NSString *newStr = [[NSString alloc] initWithFormat:str arguments:args];
        va_end(args);
        [self writeToLocation:@"/dev/stdout" withString:newStr];

    }
}

//Private
-(void)writeToLocation:(NSString *)location withString:(NSString*)str {
    if (![str hasSuffix:@"\n"]) str = [str stringByAppendingString:@"\n"];
    [str writeToFile:location atomically:NO encoding:NSUTF8StringEncoding error:nil];
}

@end
