/*
 * Scamp5d M0 Example 6 - A2D D2A Conversion
 *
 * A2D conversion can be used when a AREG image need to be stored over long period of time.
 * Degradation of AREG image is also demonstrated in this example.
 * When the DREG refresh is turned off, degradation of DREG image can also been observed.
 *
 * 1D cellular automata
 * Rule 30
 *
 * 09/11/2021
 */

#include <scamp5.hpp>

using namespace SCAMP5_PE;


// Global Variables

const dreg_t dreg_map[5] = { R9, R8, R7, R6, R5 };


int main(){

    /*
     * M0 Initialization
     */
	// initialize M0 system
	vs_init();

    /*
     * Setup Host User GUI
     */

	vs_gui_set_info(VS_M0_PROJECT_INFO_STRING);

    auto display_1 = vs_gui_add_display("original",0,0,2);
//    auto display_2 = vs_gui_add_display("D2A restored",0,1);
//    auto display_3 = vs_gui_add_display("digital bit",1,0);


    /*
     * Frame Loop
     */

    while(1){
    	// sync with frame trigger timing and process interaction with host
    	vs_frame_loop_control();

		//initilisation
    	//R5 is the source image
		scamp5_kernel_begin();
		  CLR(R5);
		  CLR(R6);
		  ALL();
		scamp5_kernel_end();

		scamp5_draw_begin(R5);
		  scamp5_draw_point(0, 127);
		scamp5_draw_end();

		//draw rules on R6


		// readout register image for inspection
		scamp5_output_image(R5,display_1);


    }

    return 0;
}

