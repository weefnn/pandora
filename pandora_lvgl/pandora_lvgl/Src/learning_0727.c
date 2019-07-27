#include "main.h"
#include "lvgl/lvgl.h"
#include "stdio.h"

void Layer_create(void)
{
    /*Create a screen*/
    lv_obj_t * scr = lv_obj_create(NULL, NULL);
    lv_scr_load(scr);          /*Load the screen*/

    /*Create 2 buttons*/
    lv_obj_t * btn1 = lv_btn_create(scr, NULL);         /*Create a button on the screen*/
    lv_btn_set_fit(btn1, LV_FIT_TIGHT);                   /*Enable to automatically set the size according to the content*/
    lv_obj_set_pos(btn1, 10, 40);              	   /*Set the position of the button*/
    //lv_obj_set_top(btn1, true);
    
    lv_obj_t * btn2 = lv_btn_create(scr, btn1);         /*Copy the first button*/
    lv_obj_set_pos(btn2, 80, 80);                    /*Set the position of the button*/

    /*Add labels to the buttons*/
    lv_obj_t * label1 = lv_label_create(btn1, NULL);	/*Create a label on the first button*/
    lv_label_set_text(label1, "Button 1");          	/*Set the text of the label*/

    lv_obj_t * label2 = lv_label_create(btn2, NULL);  	/*Create a label on the second button*/
    lv_label_set_text(label2, "Button 2");            	/*Set the text of the label*/

    /*Delete the second label*/
    //lv_obj_del(label2);
    lv_obj_move_foreground(btn1); // set btn1 on foreground on default.
}

/*
Generic events
Any object can receive these events independently from their type.
I.e. these events are sent to Buttons, Labels, Sliders, etc.

Input device related
Sent when an object is pressed, released, etc by the user.
LV_EVENT_PRESSED The object has been pressed
LV_EVENT_PRESSING The object is being pressed (sent continuously while pressing)
LV_EVENT_PRESS_LOST Still pressing but slid from the objects
LV_EVENT_SHORT_CLICKED Released before lLV_INDEV_LONG_PRESS_TIME. Not called if dragged.
LV_EVENT_LONG_PRESSED Pressing for LV_INDEV_LONG_PRESS_TIME time. Not called if dragged.
LV_EVENT_LONG_PRESSED_REPEAT Called after LV_INDEV_LONG_PRESS_TIME in every LV_INDEV_LONG_PRESS_REP_TIME ms. Not called if dragged.
LV_EVENT_CLICKED Called on release if not dragged (regardless to long press)
LV_EVENT_RELEASED Called in every case when the object has been released even if it was dragged.
Not called if slid from the object while pressing and released outside of the object. In this case, LV_EVENT_PRESS_LOST is sent.

Pointer related
These events are sent only by pointer-like input devices (E.g. mouse or touchpad)
LV_EVENT_DRAG_BEGIN Dragging of the object has started
LV_EVENT_DRAG_END Dragging finished (including drag throw)
LV_EVENT_DRAG_THROW_BEGIN Drag throw started (released after drag with  momentum)
*/
static void my_event_cb(lv_obj_t * obj, lv_event_t event)
{
    switch(event) {
        case LV_EVENT_PRESSED:
            printf("Pressed\n");
            break;

        case LV_EVENT_SHORT_CLICKED:
            printf("Short clicked\n");
            break;

        case LV_EVENT_CLICKED:
            printf("Clicked\n");
            break;

        case LV_EVENT_LONG_PRESSED:
            printf("Long press\n");
            break;

        case LV_EVENT_LONG_PRESSED_REPEAT:
            printf("Long press repeat\n");
            break;

        case LV_EVENT_RELEASED:
            printf("Released\n");
            break;
    }

    printf("Button1 callback = %d\n",event);
       /*Etc.*/
}
void Event_create(void)
{
    /*Create a screen*/
    lv_obj_t * scr = lv_obj_create(NULL, NULL);
    lv_scr_load(scr);          /*Load the screen*/

    /*Create 2 buttons*/
    lv_obj_t * btn1 = lv_btn_create(scr, NULL);         /*Create a button on the screen*/
    lv_btn_set_fit(btn1, LV_FIT_TIGHT);                   /*Enable to automatically set the size according to the content*/
    lv_obj_set_pos(btn1, 50, 30);              	   /*Set the position of the button*/
    lv_obj_set_size(btn1, 20, 10);
    /*Add labels to the buttons*/
    lv_obj_t * label1 = lv_label_create(btn1, NULL);	/*Create a label on the first button*/
    lv_label_set_text(label1, "Button 1");          	/*Set the text of the label*/

    lv_obj_set_event_cb(btn1, my_event_cb);   /*Assign an event callback*/
    //lv_obj_set_event_cb(list_btn, list_btn_event_handler);
    printf("Button init..\n");
}


/*
Style properties
common, body, text, image and line.
body:
Used by the rectangle-like objects
Text:
Used by the objects which show texts
Image :
Used by image-like objects or icons on objects
Line :
Used by objects containing lines or line-like elements
*/
void Style_create(void)
{
    static lv_style_t style1;
    lv_style_copy(&style1, &lv_style_plain);
    style1.body.main_color = LV_COLOR_WHITE;
    style1.body.grad_color = LV_COLOR_BLUE;
    style1.body.radius = 10;
    style1.body.border.color = LV_COLOR_GRAY;
    style1.body.border.width = 2;
    style1.body.border.opa = LV_OPA_50;
    style1.body.padding.left = 5;
    style1.body.padding.right = 5;
    style1.body.padding.top = 5;
    style1.body.padding.bottom = 5;
    style1.text.color = LV_COLOR_RED;
    
    /*Create a simple project*/
    lv_obj_t *obj1 = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_style(obj1, &style1);
    lv_obj_set_pos(obj1, 20, 20);
    //lv_obj_set_size(obj1, 240, 240);
    
    lv_obj_t *label = lv_label_create(obj1, NULL);
    lv_obj_align(label, obj1, LV_ALIGN_CENTER, 0, 0);
//    lv_obj_set_pos(label, 100, 0);
//    lv_obj_set_size(label, 80, 40);
    
    /*Create a bar*/
    lv_obj_t *bar1 = lv_bar_create(lv_scr_act(), NULL);
    lv_bar_set_style(bar1, LV_BAR_STYLE_INDIC, &style1);
    lv_bar_set_value(bar1, 70, NULL);
    //lv_obj_set_pos(bar1, 20, 200);
    lv_obj_align(bar1, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
}

void theme_create(void)
{
    /*Create a default slider*/
    lv_obj_t *slider = lv_slider_create(lv_scr_act(), NULL);
    lv_slider_set_value(slider, 70, NULL);
    lv_obj_set_pos(slider, 10, 10);

    /*Initialize the alien theme with a reddish hue*/
    lv_theme_t *th = lv_theme_alien_init(10, NULL);

    /*Create a new slider and apply the themes styles*/
    slider = lv_slider_create(lv_scr_act(), NULL);
    lv_slider_set_value(slider, 70, NULL);
    lv_obj_set_pos(slider, 10, 50);

    lv_slider_set_style(slider, LV_SLIDER_STYLE_BG, th->style.slider.bg);
    lv_slider_set_style(slider, LV_SLIDER_STYLE_INDIC, th->style.slider.indic);
    lv_slider_set_style(slider, LV_SLIDER_STYLE_KNOB, th->style.slider.knob);
}

