#include "../unity/src/unity.h"
#include "../include/cub3d.h"

# define RED "\033[31m"      // Red text
# define GREEN "\033[32m"    // Green text
# define YELLOW "\033[33m"   // Yellow text
# define BLUE "\033[34m"     // Blue text
# define MAGENTA "\033[35m"  // Magenta text
# define CYAN "\033[36m"     // Cyan text
# define WHITE "\033[37m"    // White text
# define RST "\033[0m"     // Resets all text attributes

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}
void test1(void) {
    printf("TEST 1 - ");
    printf(BLUE"correct map file (file.cub)\n"RST);
    TEST_ASSERT_EQUAL_INT(1, map_file_validation("file.cub"));
}

void test2(void) {
    printf("TEST 2 - ");
    printf(BLUE"incorrect map file (file.cubd)\n"RST);
    TEST_ASSERT_EQUAL_INT(0, map_file_validation("file.cubd"));
}

void test3(void) {
    printf("TEST 3 - ");
    printf(BLUE"incorrect map file (file.cue)\n"RST);
    TEST_ASSERT_EQUAL_INT(0, map_file_validation("file.cue"));
}

void test4(void) {
    printf("TEST 4 - ");
    printf(BLUE"incorrect map file (file)\n"RST);
    TEST_ASSERT_EQUAL_INT(0, map_file_validation("file"));
}
void test5(void) {

    printf("TEST 5 - ");
    printf(BLUE"numbers only array\n"RST);

    t_game data;
    int    fd1 = open("file.cub", O_RDONLY);
    data.fd = fd1;
    parsing(&data);
    TEST_ASSERT_EQUAL_STRING("111111111111111", data.map[0]);
    TEST_ASSERT_EQUAL_STRING("100000000000001", data.map[1]);
    TEST_ASSERT_EQUAL_STRING("111111111111111", data.map[7]);
    TEST_ASSERT_EQUAL_STRING(NULL, data.map[8]);
    TEST_ASSERT_EQUAL_STRING("100001000000001", data.map[6]);
}


void test6(void) {
    printf("TEST 6 - ");
    printf(BLUE"111111111 map line\n"RST);
    TEST_ASSERT_EQUAL_INT(1, elements_checker("11111111"));
}

void test7(void) {
    printf("TEST 7 - ");
    printf(BLUE"111011111 map line\n"RST);
    TEST_ASSERT_EQUAL_INT(1, elements_checker("11101111"));
}

void test8(void) {
    printf("TEST 8 - ");
    printf(BLUE"011011111 map line (incorrect)\n"RST);
    TEST_ASSERT_EQUAL_INT(0, elements_checker("01101111"));
}

void test9(void) {
    printf("TEST 9 - ");
    printf(BLUE"111011110 map line (incorrect)\n"RST);
    TEST_ASSERT_EQUAL_INT(0, elements_checker("111011110"));
}

void test10(void) {

    printf("TEST 10 - ");
    printf(BLUE"small rectangle map 6 x 5\n"RST);
    int ret;

    t_game data;
    int    fd1 = open("file2.cub", O_RDONLY);
    data.fd = fd1;
    ret = parsing(&data);
    TEST_ASSERT_EQUAL_STRING("111111", data.map[0]);
    TEST_ASSERT_EQUAL_STRING("100001", data.map[1]);
    TEST_ASSERT_EQUAL_STRING("1000N1", data.map[2]);
    TEST_ASSERT_EQUAL_STRING("100001", data.map[3]);
    TEST_ASSERT_EQUAL_STRING("111111", data.map[4]);
    TEST_ASSERT_EQUAL_STRING(NULL, data.map[5]);
    TEST_ASSERT_EQUAL_INT(1, ret);
}


// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    printf("\n");
    printf(GREEN"MAP FILE VALIDATION\n"RST);
    RUN_TEST(test1);
    printf("\n");
    RUN_TEST(test2);
    printf("\n");    
    RUN_TEST(test3);
    printf("\n");
    RUN_TEST(test4);
    printf("\n");
    printf(GREEN"CREATING MAP ARRAY\n"RST);
    RUN_TEST(test5);
    printf("\n");    
    RUN_TEST(test6);
    printf("\n");
    RUN_TEST(test7);
    printf("\n");
    RUN_TEST(test8);
    printf("\n");
    RUN_TEST(test9);
    printf("\n");
    RUN_TEST(test10);
    printf("\n");
    return UNITY_END();
}