#include <data/data.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 8) {
        std::cerr << "Usage: " << argv[0] << "<type> <numPoints> <blurCoefficient> <phi_1> <theta_1> <phi_2> <theta_2> [phi_3 theta_3 phi_4 theta_4]" << std::endl;
        return 1;
    }

    std::string type = argv[1];
    int numPoints = std::stoi(argv[2]);
    double blurCoefficient = std::stod(argv[3]);
    double phi_1 = std::stod(argv[4]);
    double theta_1 = std::stod(argv[5]);
    double phi_2 = std::stod(argv[6]);
    double theta_2 = std::stod(argv[7]);

    std::string filename;
    std::string filename1;

    SphericalCoordinatesGenerator generator;
   if (type == "one_arc") {
        filename = "one_noisy_arc_coordinates.txt";
        std::vector<std::vector<double>> points = generator.generatePointsOnArc(numPoints, phi_1, theta_1, phi_2, theta_2);
        std::vector<std::vector<double>> noisyPoints = generator.addCoordinateNoiseOnSphere(points, blurCoefficient);
        generator.writePointsToFile(filename, noisyPoints);
    }
//   else if(type == "from_point"){
//        if(argc < 11){
//            std::cerr << "Usage for type from_point: " << argv[0] << "<type> <numPoints> <blurCoefficient> <phi_1> <theta_1> <phi_2> <theta_2> <phi_3> <theta_3> numArcs" << std::endl;
//            return 1;
//        }
//        filename = "noisy_arcs_from_point.txt";
//        double phi_3 = std::stod(argv[8]);
//        double theta_3 = std::stod(argv[9]);
//        double numArcs = std::stod(argv[10]);
//        std::vector<std::vector<double>> points = generator.generatePointsFromCenter(numArcs, numPoints, phi_1, theta_1, phi_2, theta_2, phi_3, theta_3);
//        std::vector<std::vector<double>> noisyPoints = generator.addCoordinateNoiseOnSphere(points, blurCoefficient);
//        generator.writePointsToFile(filename, noisyPoints);
//    }
   else if (type == "two_arcs") {
        if (argc < 12) {
            std::cerr << "Usage for type two_arcs: " << argv[0] << " <type> <numPoints> <blurCoefficient> <phi_1> <theta_1> <phi_2> <theta_2> <phi_3> <theta_3> <phi_4> <theta_4>" << std::endl;
            return 1;
        }
        filename = "first_noisy_arc_coordinates.txt";
        std::vector<std::vector<double>> points1 = generator.generatePointsOnArc(numPoints, phi_1, theta_1, phi_2, theta_2);
        std::vector<std::vector<double>> noisyPoints1 = generator.addCoordinateNoiseOnSphere(points1, blurCoefficient);
        generator.writePointsToFile(filename, noisyPoints1);


        filename1 = "second_noisy_arc_coordinates.txt";
        double phi_3 = std::stod(argv[8]);
        double theta_3 = std::stod(argv[9]);
        double phi_4 = std::stod(argv[10]);
        double theta_4 = std::stod(argv[11]);
        std::vector<std::vector<double>> points2 = generator.generatePointsOnArc(numPoints, phi_3, theta_3, phi_4, theta_4);
        std::vector<std::vector<double>> noisyPoints2 = generator.addCoordinateNoiseOnSphere(points2, blurCoefficient);
        generator.writePointsToFile(filename1, noisyPoints2);
   }
   else {
        std::cerr << "Invalid type. Supported types" << std::endl;
        return 1;
   }
    // Output the read data
    //std::vector<std::vector<double>> readPoints = generator.readPointsFromFile(filename);
    // return 0;
}


