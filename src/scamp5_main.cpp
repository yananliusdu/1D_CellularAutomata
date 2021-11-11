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
 *
 * Rule 90 can be implemented directly using XOR
 */

#include <scamp5.hpp>
#include "rule.hpp"

using namespace SCAMP5_PE;

// Global Variables
const dreg_t load_dreg[6] = { R10, R9, R8, R7, R6, R5 };

//functions
void load_dreg_image(DREG target_dreg,const uint8_t*image_buffer,uint16_t n_rows);
void refresh_dreg_storage();




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

    auto display_1 = vs_gui_add_display("",0,0,2);
//    auto display_2 = vs_gui_add_display("rule",0,2,2);
//    auto display_3 = vs_gui_add_display("digital bit",1,0);
    int iterations;
    vs_gui_add_slider("iterations", 1,255,1,&iterations);

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
		  ALL();
		scamp5_kernel_end();
		scamp5_draw_begin(R5);
		  scamp5_draw_point(0, 127);
		scamp5_draw_end();
		//draw rules on R6
		//load a rule template for R6 as the update rule of CA
		//load_dreg_image(R6, rule30, 256);

		//update
		scamp5_kernel_begin();
		   all();
		   MOV(R6,R5);
		scamp5_kernel_end();

		for(int i = 1; i <= iterations; i++)
		{
			scamp5_kernel_begin();
			   MOV(R5,R6);
			   DNEWS(R0,R6,west);
			   DNEWS(R6,R0,west);
			   XOR(R7,R5,R6);
			   DNEWS(R0,R7,north);
			   DNEWS(R6,R0,east);
			   OR(R6,R5);
			scamp5_kernel_end();
		}

		// readout register image for inspection
		scamp5_output_image(R6,display_1);
//		scamp5_output_image(R6,display_2);


    }

    return 0;
}



void load_dreg_image(DREG target_dreg,const uint8_t*image_buffer,uint16_t n_rows)
{
	const size_t row_bytes = n_rows/8;
    scamp5_dynamic_kernel_begin();
    	CLR(target_dreg);
	scamp5_dynamic_kernel_end();
    scamp5_draw_begin(target_dreg);
    for(int r=0;r<n_rows;r++){
		const uint8_t*row_array = &image_buffer[r*row_bytes];
		int u = 0;
		while(u<32){
			if(row_array[u]==0x00){
				u += 1;
			}else
			if(row_array[u]==0xFF){
				int u0 = u;
				int u1 = u;
				u += 1;
				while(u<32){
					if(row_array[u]==0xFF){
						u1 = u;
						u += 1;
					}else{
						break;
					}
				};
				scamp5_draw_rect(r,u0*8,r,u1*8 + 7);
			}else{
				uint8_t w = row_array[u];
				uint8_t m = 1;
				for(int c=u*8;c<(u*8 + 8);c++){
					if(w&m){
						scamp5_draw_pixel(r,c);
					}
					m <<= 1;
				}
				u += 1;
			}
		}
		if(r%16==0){
			refresh_dreg_storage();
		}
	}
	scamp5_draw_end();
}

void refresh_dreg_storage(){
	scamp5_kernel_begin();
		REFRESH(load_dreg[0]);
		REFRESH(load_dreg[1]);
		REFRESH(load_dreg[2]);
		REFRESH(load_dreg[3]);
		REFRESH(load_dreg[4]);
		REFRESH(load_dreg[5]);
		REFRESH(load_dreg[6]);
	scamp5_kernel_end();
}
