//
//  main_test.c
//  Week 4 
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "min_unit.h"
#include "core.h"

static char * test_highest_scorer() {
    mu_begin_case("highest_scorer");
    
    int r0 = highest_scorer(NULL, NULL);
    mu_assert_i("highest_scorer(NULL, NULL) should return FALSE", 0, r0);

    char f1_contents[] = "Ashley 80";
    FILE * f1 = fmemopen(f1_contents, strlen(f1_contents), "r");
    int r1 = highest_scorer(NULL, f1);
    mu_assert_i("highest_scorer(NULL, fp) should return FALSE", 0, r1);
    fclose(f1);

    char b2[21]; 
    int r2 = highest_scorer(b2, NULL);
    mu_assert_i("highest_scorer(buffer, NULL) should return FALSE", 0, r2);


    char f3_contents[] = "Ashley 80\nJohn 95\nJim 30";
    FILE * f3 = fmemopen(f3_contents, strlen(f3_contents), "r");
    char b3[21]; 
    int r3 = highest_scorer(b3, f3);

    mu_assert_i("highest_scorer(buffer, fp) should return TRUE", 1, r3);
    mu_assert_s("Highest score should be John", "John", b3);
    fclose(f3);

    char f4_contents[] = "A_NAME_WITH_20_CHARS 99\nJohn 95\nJim 30";
    FILE * f4 = fmemopen(f4_contents, strlen(f4_contents), "r");
    char b4[21]; 
    int r4 = highest_scorer(b4, f4);

    mu_assert_i("highest_scorer(buffer, fp) should return TRUE", 1, r4);
    mu_assert_s("Highest score should be A_NAME_WITH_20_CHARS", "A_NAME_WITH_20_CHARS", b4);
    fclose(f4);

    mu_end_case("highest_scorer");
    return 0;
}

static char * test_add_score() {
    mu_begin_case("add_score");

    int r0 = add_score(NULL, 0, NULL); 
    mu_assert_i("add_score(NULL, 0, NULL) should return FALSE", 0, r0);

    int r1 = add_score("Scott", 0, NULL);
    mu_assert_i("add_score(\"Scott\", 0, NULL) should return FALSE", 0, r1);

    size_t size = 1000;
    char f2_contents[1000];
    char * f2_pointer = f2_contents;
    memset(f2_contents, '\0', 1000);
    FILE * f2 = open_memstream(&f2_pointer, &size);
    int r2 = add_score("Scott", 15, f2);
    fflush(f2);
    mu_assert_i("add_score(\"Scott\", 15, f2) should return TRUE", 1, r2);
    mu_assert_s("Expect value written to file", "Scott 15\n", f2_pointer);

    size_t size3 = 1000;
    char f3_contents[1000];
    char * f3_pointer = f3_contents;
    memset(f3_contents, '\0', 1000);
    FILE * f3 = open_memstream(&f3_pointer, &size3);
    fprintf(f3, "Jim 30\nPam 31\n");
    int r3 = add_score("Scott", 15, f3);
    fflush(f3);
    mu_assert_i("add_score(\"Scott\", 15, f2) should return TRUE", 1, r3);
    mu_assert_s("Expect value written to file", "Jim 30\nPam 31\nScott 15\n", f3_pointer);

    mu_end_case("add_score");
    return 0;
}

static char * all_tests() {
    test_highest_scorer();
    test_add_score();
    return 0;
}

#ifdef TEST
int main(int argc, char **argv) {
    mu_run(all_tests);
    
    return 0;
}
#endif
