//
//  testcase.cpp
//  evil-monkeys
//
//  Created by phuong on 5/13/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "catch.hpp"

#include "level.hpp"

using namespace EvilMonkeys;

TEST_CASE("Testing Sample Class") {
    DrawEngine de;
    Level lvl(&de);
    
    SECTION("setting the str") {
        INFO("Using TestStr") // Only appears on a FAIL
        
        
//        sc.setStr("TestStr");
        
        lvl.addEnemies(3);
        
        std::list <Sprite *>::const_iterator Iter;
        
        std::list <Sprite *> npc = lvl.npc;
        int count = 0;
        for (Iter = npc.begin(); Iter != npc.end(); ++Iter) {
            ++count;
        }
        
        CAPTURE(count); // Displays this variable on a FAIL
        
        CHECK(count == 3);
    }
    
//    SECTION("test bigStr") {
//        sc.setStr("TestStr");
//        REQUIRE(sc.bigStr() == "TestStr : 7");
//    }
//    
//    SECTION("Test doubles") {
//        sc.setD(1);
//        CHECK(sc.getD() == 1);
//        sc.setD(1.0/3.0);
//        CHECK(sc.getD() == Approx(0.33333)); // Nice
//    }
}

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(0) == 1 );
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}


TEST_CASE( "vectors can be sized and resized", "[vector]" ) {
    
    std::vector<int> v( 5 );
    
    REQUIRE( v.size() == 5 );
    REQUIRE( v.capacity() >= 5 );
    
    SECTION( "resizing bigger changes size and capacity" ) {
        v.resize( 10 );
        
        REQUIRE( v.size() == 10 );
        REQUIRE( v.capacity() >= 10 );
    }
    SECTION( "resizing smaller changes size but not capacity" ) {
        v.resize( 0 );
        
        REQUIRE( v.size() == 0 );
        REQUIRE( v.capacity() >= 5 );
    }
    SECTION( "reserving bigger changes capacity but not size" ) {
        v.reserve( 10 );
        
        REQUIRE( v.size() == 6 );
        REQUIRE( v.capacity() >= 10 );
    }
    SECTION( "reserving smaller does not change size or capacity" ) {
        v.reserve( 0 );
        
        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 5 );
    }
}



SCENARIO( "vectors can be sized and resized", "[vector]" ) {
    
    GIVEN( "A vector with some items" ) {
        std::vector<int> v( 5 );
        
        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 5 );
        
        WHEN( "the size is increased" ) {
            v.resize( 10 );
            
            THEN( "the size and capacity change" ) {
                REQUIRE( v.size() == 10 );
                REQUIRE( v.capacity() >= 10 );
            }
        }
        WHEN( "the size is reduced" ) {
            v.resize( 0 );
            
            THEN( "the size changes but not capacity" ) {
                REQUIRE( v.size() == 0 );
                REQUIRE( v.capacity() >= 5 );
            }
        }
        WHEN( "more capacity is reserved" ) {
            v.reserve( 10 );
            
            THEN( "the capacity changes but not the size" ) {
                REQUIRE( v.size() == 5 );
                REQUIRE( v.capacity() >= 11 );
            }
        }
        WHEN( "less capacity is reserved" ) {
            v.reserve( 0 );
            
            THEN( "neither size nor capacity are changed" ) {
                REQUIRE( v.size() == 5 );
                REQUIRE( v.capacity() >= 5 );
            }
        }
    }
}

TEST_CASE( "stupid/1=2", "Prove that one equals 2" )
{
    int one = 1;
    REQUIRE( one == 2 );
}


TEST_CASE( "example/less than 7", "The number is less than 7" )
{
    int notThisOne = 7;
    
    for( int i=0; i < 7; ++i )
    {
        REQUIRE( notThisOne > i+1  );
    }
}


TEST_CASE( "example/less than 7 again", "The number is less than 7" )
{
    int notThisOne = 7;
    
    for( int i=0; i < 7; ++i )
    {
        INFO( "i=" << i );
        REQUIRE( notThisOne > i+1  );
    }
}
