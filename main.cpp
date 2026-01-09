#include <iostream>
#include <herzlich.h>

#ifdef USE_GLFW
    #include <GLFW/glfw3.h>
#endif

#ifdef USE_ADDER
    #include <adder.h>
#endif

int main(int argc, char** argv) {
    std::cout << argv[0] << " Version " << HERZLICH_MAJOR_VERSION << "." << HERZLICH_MINOR_VERSION << std::endl;

#ifdef USE_ADDER
    std::cout << "Adder library support: ENABLED" << std::endl;
#else
    std::cout << "Adder library support: DISABLED" << std::endl;
#endif

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <arg1> <arg2>" << std::endl;
        return EXIT_FAILURE;
    }
    
    int num1, num2;
    if (argv[1][0] >= 'a' && argv[1][0] <= 'z') {
        num1 = argv[1][0];
    } else {
        num1 = std::atoi(argv[1]);
    }
    
    if (argv[2][0] >= 'a' && argv[2][0] <= 'z') {
        num2 = argv[2][0]; 
    } else {
        num2 = std::atoi(argv[2]); 
    }
    
#ifdef USE_ADDER
    std::cout << "Result: " << tuto::add(num1, num2) << std::endl;
#else
    std::cout << "Result: " << (num1 + num2) << std::endl;
#endif
    
#ifdef USE_GLFW
    GLFWwindow* window;

    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    window = glfwCreateWindow( 300, 300, "Gears", NULL, NULL );
    if (!window)
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    while( !glfwWindowShouldClose(window) )
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
#endif

    exit( EXIT_SUCCESS );
}