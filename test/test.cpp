#include <catch2/catch_test_macros.hpp>
#include <iostream>

// change if you choose to use a different header name
#include "CampusCompass.h"
using namespace std;

TEST_CASE("Inavlid commands") {
    CampusCompass compass;
    compass.parseCSV("../data/edges.csv", "../data/classes.csv");

    // invalid command
    REQUIRE(compass.parseCommand("notReal \"Ashtyn\" 12341234 1 1 COP3530") == false);

    // invalid ID
    REQUIRE(compass.parseCommand("insert \"Ashtyn\" 1234L234 1 1 COP3530") == false);

    // Invalid Name
    REQUIRE(compass.parseCommand("insert \"Ashtyn3\" 12345678 1 1 COP3530") == false);

    // Wrong number of classes
    REQUIRE(compass.parseCommand("insert \"Ashtyn\" 12341234 1 2 COP3530") == false);

    // Invalid class codes
    REQUIRE(compass.parseCommand("insert \"Ashtyn\" 12345678 1 1 cop3530") == false);
    REQUIRE(compass.parseCommand("insert \"Ashtyn\" 12345678 1 1 COPP3530") == false);
}

TEST_CASE("Edge Cases") {
    CampusCompass compass;
    compass.parseCSV("../data/edges.csv", "../data/classes.csv");
    bool insertion = compass.insert("Ashtyn", 12345678, "1", {"COP3530"});
    REQUIRE(insertion == true);

    // Student doesn't exist
    REQUIRE(compass.remove(12345679) == false);

    // replace nonexistent class
    REQUIRE(compass.replaceClass(12345678, "GAP3232", "COP3504") == false);

    // Student is deleted after dropping last class
    REQUIRE(compass.dropClass(12345678, "COP3530") == true);
    REQUIRE(compass.remove(12345678) == false);
}

TEST_CASE("dropClass, removeClass, remove, and replaceClass") {
    CampusCompass compass;
    compass.parseCSV("../data/edges.csv", "../data/classes.csv");
    REQUIRE(compass.insert("Brandon", 11110000, "1", {"COP3530", "COP3502", "COT3100"}) == true);
    REQUIRE(compass.insert("Sarah",   22220000, "2", {"COP3530", "COP3503"}) == true);;

    // removeClass test
    int removed = compass.removeClass("COP3530");
    REQUIRE(removed == 2);

    // dropClass test
    REQUIRE(compass.dropClass(22220000, "COP3503") == true);
    REQUIRE(compass.remove(22220000) == false);

    // replaceClass and remove tests
    REQUIRE(compass.replaceClass(11110000, "COP3502", "COP3503") == true);
    REQUIRE(compass.dropClass(11110000, "COP3503") == true);
    REQUIRE(compass.remove(11110000) == true);

}

TEST_CASE("printShortestEdges test") {
    CampusCompass compass;
    compass.parseCSV("../data/edges.csv", "../data/classes.csv");

    compass.insert("Ashtyn", 11111111, "43", {"PHY2048", "IDS2935"}); // PHY2048 only has 1 edge

    // Testing with valid path to both
    vector<pair<string, int>> result = compass.printShortestEdges(11111111);
    vector<pair<string, int>> expected = {make_pair("IDS2935", 2), make_pair("PHY2048", 9)};
    REQUIRE(result == expected);

    // Testing with valid path to only one class
    compass.toggleEdgeClosure("49", "56");
    REQUIRE(compass.checkEdgeStatus("49", "56") == 0);
    result = compass.printShortestEdges(11111111);
    expected = {make_pair("IDS2935", 2), make_pair("PHY2048", -1)};
    REQUIRE(result == expected);
}