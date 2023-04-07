//
// Created by perseverance on 31.03.2023.
//

#include <gtest/gtest.h>
#include "../src/rv_to_Kepler/rv_to_Kepler.h"

TEST(rv_Keplertest, first_test) {
    basis<double> IJK = {{1, 0, 0},
                         {0, 1, 0},
                         {0, 0, 1}};

    std::vector<double> r = {6524.834, 6862.875, 6448.296};
    std::vector<double> v = {4.901327, 5.533756, -1.976341};

    Kepler_elements<double> Kepler(IJK, r, v);
    //Kepler_elements(IJK, r, v);
    std::vector<double> h = Kepler.get_h();

    std::cout << "r_coords: " << std::endl;
    for (auto i: r) {
        std::cout << i << std::endl;
    }

    std::cout << "v_coords: " << std::endl;
    for (auto i: v) {
        std::cout << i << std::endl;
    }

    std::cout << "r magnitude: " << norm(r) << std::endl;
    std::cout << "v magnitude: " << norm(v) << std::endl;

    std::cout << "Specific angular momentum coords: " << std::endl;
    for (auto i: h) {
        std::cout << i << std::endl;
    }
    std::cout << "The magnitude of angular momentum is " << Kepler.get_h_norm() << std::endl;
    std::vector<double> N = Kepler.get_N();
    std::cout << "Let us find out the node Vector N coords:  " << std::endl;
    for (auto i: N) {
        std::cout << i << std::endl;
    }
    std::cout << "Node Vector N magnitude:  " << Kepler.get_N_norm() << std::endl;
    std::cout << "Ksi is: " << Kepler.get_ksi() << std::endl;

    std::cout << "The excentry coords" << std::endl;

    for (auto i: Kepler.get_Excentryvect()) {
        std::cout << i << std::endl;
    }
    std::cout << "Eccentricity: " << Kepler.get_Excentry() << std::endl;

    std::cout << "axle shaft: " << Kepler.get_a() << std::endl;
    std::cout << "semiparametr: " << Kepler.get_p() << std::endl;

    std::cout << "inclination (rad): " << Kepler.get_i() << std::endl;

/*    std::cout << Kepler.get_sdsdfsdfgsdgfsdgsd() << std::endl;
    std::cout << acos(Kepler.get_sdsdfsdfgsdgfsdgsd());*/

    std::cout << "Right ascension of the ascending node (W): " << Kepler.get_W() << std::endl;
    //std::cout << Kepler.get_sdsdfsdfgsdgfsdgsd();
    std::cout << "Argument of perigee: " << Kepler.get_w() << std::endl;
    std::cout << "True anomaly: " << Kepler.get_nu() << std::endl;
    std::cout << "Orbital elements: " << std::endl;
    for(auto i : Kepler.get_orbital_elements()){
        std::cout << i << std::endl;
    }
}

TEST(rv_Keplertest, second_test){
    basis<double> IJK = {{1, 0, 0},
                         {0, 1, 0},
                         {0, 0, 1}};

    std::vector<double> r = {6524.834, 6862.875, 6448.296};
    std::vector<double> v = {4.901327, 5.533756, -1.976341};

    Kepler_elements<double> Kepler(IJK, r, v);
    Kepler.cout_orbital_elements();
}
TEST(rv_Keplertest, third_test){
    basis<double> IJK = {{1, 0, 0},
                         {0, 1, 0},
                         {0, 0, 1}};

    std::vector<double> r = {-466.7639, 11447.0219, 0};
    std::vector<double> v = {-5.996222, 4.753601, 0};
    std::vector<double> orbital_elements = {1.5184364, 3.9618974, 0.9250245, 0.83285, 36126, 1.60570291,11067.790};

    Kepler_elements<double> Kepler(IJK, r, v);
    std::vector<double> exp_elements = Kepler.get_orbital_elements();
    //std::cout << Kepler.get_a();
    Kepler.cout_orbital_elements();
/*    for(auto i = 0; i < exp_elements.size(); ++i){
        ASSERT_NEAR(orbital_elements[i], exp_elements[i], 0.001);
    }*/
}