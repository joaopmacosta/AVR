#include "../../Inc/driver/flow_sensor.h"
#include "../../Inc/driver/io.h"
#include "../../Inc/core/clock.h"
#include "../../TC_driver/avr_compiler.h"
#include "../../config.h"

// VARS
uint16_t flow1 = 0;
uint16_t flowTimer = 0;
uint16_t flow1ml = 0;
uint16_t flow1Ticks = 0;
uint16_t qtyWater1 = 0;

//end stop1
int switch1 = 1;
int last_switch1;
int end_stop1 = 0;

void update_flows(void)
{
  //if (T0_millis - flowTimer >= FLOW_REFRESH_TIME)
  //{
    // The flow sensor outputs 4.5 pulses per second per litre/minute of flow.
    //float calibrationFactor = 4.5 * (4250/500) ; //4.5;
    
    // Because this loop may not complete in exactly 1 second intervals we calculate
    // the number of milliseconds that have passed since the last execution and use
    // that to scale the output. We also apply the calibrationFactor to scale the output
    // based on the number of pulses per second per units of measure (litres/minute in
    // this case) coming from the sensor.
    flow1 = (((FLOW_REFRESH_TIME / (T0_millis - flowTimer)) * flow1Ticks) / CALIBRATION_FACTOR)/60*1000;
    //flow2 = (((FLOW_REFRESH_TIME / (T0_millis - flowTimer)) * flow2Ticks) / CALIBRATION_FACTOR)/60*1000;
    // Note the time this processing pass was executed. Note that because we've
    // disabled interrupts the millis() function won't actually be incrementing right
    // at this point, but it will still return the value it was set to just before
    // interrupts went away.

    flowTimer = T0_millis;

    // Divide the flow rate in litres/minute by 60 to determine how many litres have
    // passed through the sensor in this 1 second interval, then multiply by 1000 to
    // convert to millilitres.
    flow1ml = (flow1 / 60) * 1000;
    //flow2ml = (flow2 / 60) * 1000;
    
    // Add the millilitres passed in this second to the cumulative total
    qtyWater1 += flow1;
    //qtyWater2 += flow2;

    spew("ticks: %d | flow: %d | flow(ml): %d | qty: %d\n", flow1Ticks, flow1, flow1ml, qtyWater1);

    flow1 = 0;
    flow1Ticks = 0;
  //}
}

float measure_water_level(void){
  return 100.1;
}

ISR(PORTA_INT0_vect)
{
  flow1Ticks++;
}

ISR(PORTC_INT0_vect)
{
  GPIO_TGL(LED);
}