//
//  core.h
//  Week 4 
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//

#ifndef core_h
#define core_h

#define TRUE 1;
#define FALSE 0;

int highest_scorer(char * buffer, FILE * stream);
int add_score(char * name, int score, FILE * stream); 
int core_main(int argc, const char * argv[]);

#endif /* core_h */
