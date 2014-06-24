//
//  JRLogger.m
//  kanban-fetch
//
//  Created by Jan-Yves on 27/05/14.
//  Copyright (c) 2014 Jan-Yves Ruzicka. All rights reserved.
//

#import "JRLogger.h"

static JRLogger *kJRLogger;

@implementation JRLogger

+(id)logger {
    if (!kJRLogger)
        kJRLogger = [[JRLogger alloc] init];
    return kJRLogger;
}

-(id)init {
    if (self = [super init]) {
        self.debugging = NO;
        self.logBuffer = [NSMutableString string];
    }
    return self;
}

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
    va_list args;
    va_start(args,str);
    NSString *newStr = [[NSString alloc] initWithFormat:str arguments:args];
    va_end(args);
    
    if (self.debugging)
        [self writeToLocation:@"/dev/stdout" withString:newStr];
    else
        [self addToBuffer:newStr];
}

-(void)fail:(NSString *)str,... {
    va_list args;
    va_start(args,str);
    NSString *newStr = [[NSString alloc] initWithFormat:str arguments:args];
    va_end(args);
    [self writeToLocation:@"/dev/stderr" withString:newStr];
    [self writeBufferToFile];
    exit(EXIT_FAILURE);
}

//Private
-(void)writeToLocation:(NSString *)location withString:(NSString*)str {
    if (![str hasSuffix:@"\n"]) str = [str stringByAppendingString:@"\n"];
    [str writeToFile:location atomically:NO encoding:NSUTF8StringEncoding error:nil];
    [self addToBuffer:str];
}

-(void)addToBuffer:(NSString *)str {
    if (![str hasSuffix:@"\n"]) str = [str stringByAppendingString:@"\n"];
    [self.logBuffer appendString:str];
}

-(void)writeBufferToFile {
    if (self.logfile) {
        NSFileManager *fm = [NSFileManager defaultManager];
        NSString *outputString;
        NSString *filePath = [self.logfile stringByStandardizingPath];
        
        //Retrieve current data
        NSData *rawLogFileContents = [fm contentsAtPath:filePath];
        if (rawLogFileContents) { //File exists
            NSString *separator = @"----------------------------------------\n";
            NSString *logFileContents = [[NSString alloc] initWithData:[fm contentsAtPath:filePath] encoding:NSUTF8StringEncoding];
            NSMutableArray *logEntries = [NSMutableArray arrayWithArray:[logFileContents componentsSeparatedByString:separator]];
        
            //Add new data + truncate if required
            [logEntries insertObject:self.logBuffer atIndex:0];
            while (logEntries.count > 100)
                [logEntries removeLastObject];
            
            outputString = [logEntries componentsJoinedByString:separator];
        }
        else
            outputString = self.logBuffer;
        
        [fm createFileAtPath:filePath contents:[outputString dataUsingEncoding:NSUTF8StringEncoding] attributes:nil];
        
    }
}

@end
