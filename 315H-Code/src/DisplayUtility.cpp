#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_btn.h"
#include "main.h"

int autonSelected = -1;
static lv_style_t matchStyle;
const int buttonW = 100;
const int buttonH = 40;

//------------------------------------------------------------------------------
lv_obj_t * match = lv_obj_create(NULL, NULL);
lv_obj_t * gui = lv_tabview_create(lv_scr_act(), NULL);
lv_obj_t * red_tab = lv_tabview_add_tab(gui, "Red Side");
lv_obj_t * blue_tab = lv_tabview_add_tab(gui, "Blue Side");
lv_obj_t * skills_tab = lv_tabview_add_tab(gui, "Skills");

lv_style_t redStyleON; // toggled on style
lv_style_t redStyleOFF; // toggled off style
lv_style_t blueStyleON; // toggled on style
lv_style_t blueStyleOFF; // toggled off style
lv_style_t skillsStyleON; // toggled on style
lv_style_t skillsStyleOFF; // toggled off style
lv_style_t selectedStyleON; // toggled on style
lv_style_t selectedStyleOFF; // toggled off style

const lv_color_t DISPLAY_RED = LV_COLOR_MAKE(243, 43, 54);
const lv_color_t DISPLAY_BLUE = LV_COLOR_MAKE(0, 143, 237);
const lv_color_t DISPLAY_YELLOW = LV_COLOR_MAKE(218, 160, 0);
const lv_color_t DISPLAY_PURPLE = LV_COLOR_MAKE(108, 0, 120);
const lv_color_t DISPLAY_WHITE = LV_COLOR_MAKE(255, 255, 255);

// Buttons
//const int NUM_SELECTION = 8;
lv_obj_t *redButtons[NUM_SELECTION];
lv_obj_t *blueButtons[NUM_SELECTION];
lv_obj_t *otherButtons[NUM_SELECTION];

void initButtons()
{
  for (int i = 0; i < NUM_SELECTION; i++)
  {
    redButtons[i] = lv_btn_create(red_tab, NULL);
    blueButtons[i] = lv_btn_create(blue_tab, NULL);
    otherButtons[i] = lv_btn_create(skills_tab, NULL);
  }
}

const char *labelText[] =
{
  "FILLER TEXT",
  // red side autons
  "Solo WP", "1 Roller", "", "",
	"", "", "", "",
  "", "", "", "",
  // blue side autons
  "Solo WP", "1 Roller", "", "",
	"", "", "", "",
  "", "", "", "",
  // other programs
	"Skills Auton", "", "", "",
  "", "", "", "",
  "", "", "", ""
};

//------------------------------------------------------------------------------
static lv_res_t switch_to_Tabview(lv_obj_t *btn)
{
	lv_scr_load(gui);
	return LV_RES_OK;
}

//------------------------------------------------------------------------------
void setMatchScreenColor (int input)
{
  lv_style_copy(&matchStyle, &lv_style_plain);
  if (input <= NUM_SELECTION)
  {
    matchStyle.body.main_color = DISPLAY_RED;
  	matchStyle.body.grad_color = DISPLAY_RED;
  }
  else if (input <= NUM_SELECTION*2)
  {
    matchStyle.body.main_color = DISPLAY_BLUE;
    matchStyle.body.grad_color = DISPLAY_BLUE;
  }
  else if (input <= NUM_SELECTION*3)
  {
    matchStyle.body.main_color = DISPLAY_YELLOW;
    matchStyle.body.grad_color = DISPLAY_YELLOW;
  }
  lv_obj_set_style(match, &matchStyle);
}

//------------------------------------------------------------------------------
static lv_res_t switch_to_Match(lv_obj_t *btn)
{
  if (autonSelected > 0)
  {
    int side = (autonSelected-1)/NUM_SELECTION;
    if (side == 0)
      setStyle(redButtons[autonSelected-1], 1);
    else if (side == 1)
      setStyle(blueButtons[autonSelected-1-NUM_SELECTION], 2);
    else
      setStyle(otherButtons[autonSelected-1-(2*NUM_SELECTION)], 3);
  }

  autonSelected = lv_obj_get_free_num(btn);

  setStyle(btn, 4);

  char *print = new char[strlen(labelText[autonSelected])+5];

  int side = (autonSelected-1)/NUM_SELECTION;
  if (side == 0)
  {
    strcpy(print, "Red ");
    strcat(print, labelText[autonSelected]);
  }
  else if (side == 1)
  {
    strcpy(print, "Blue ");
    strcat(print, labelText[autonSelected]);
  }
  else if (side == 2)
  {
    strcpy(print, labelText[autonSelected]);
  }

  //partner.clear_line(2);
  //pros::delay(100);
  //partner.print(2, 0, print);

	return LV_RES_OK;
}

//------------------------------------------------------------------------------
void setStyle (lv_obj_t *btn, int styleType)
{
  lv_btn_set_toggle(btn, true);
  lv_btn_set_action(btn, LV_BTN_ACTION_CLICK, switch_to_Match);

	if (styleType == 1)
    {
        lv_btn_set_style(btn, LV_BTN_STYLE_REL, &redStyleOFF);
        lv_btn_set_style(btn, LV_BTN_STYLE_PR, &redStyleON); //set the pressed style
        lv_btn_set_style(btn, LV_BTN_STYLE_TGL_REL, &redStyleON); //set the toggle released style
        lv_btn_set_style(btn, LV_BTN_STYLE_TGL_PR, &redStyleOFF); //set the toggle pressed style
        }
        else if (styleType == 2)
        {
            lv_btn_set_style(btn, LV_BTN_STYLE_REL, &blueStyleOFF);
            lv_btn_set_style(btn, LV_BTN_STYLE_PR, &blueStyleON); //set the pressed style
            lv_btn_set_style(btn, LV_BTN_STYLE_TGL_REL, &blueStyleON); //set the toggle released style
            lv_btn_set_style(btn, LV_BTN_STYLE_TGL_PR, &blueStyleOFF); //set the toggle pressed style
        }
        else if (styleType == 3)
        {
            lv_btn_set_style(btn, LV_BTN_STYLE_REL, &skillsStyleOFF);
            lv_btn_set_style(btn, LV_BTN_STYLE_PR, &skillsStyleON); //set the pressed style
            lv_btn_set_style(btn, LV_BTN_STYLE_TGL_REL, &skillsStyleON); //set the toggle released style
            lv_btn_set_style(btn, LV_BTN_STYLE_TGL_PR, &skillsStyleOFF); //set the toggle pressed style
        }
        else if (styleType == 4)
        {
        lv_btn_set_style(btn, LV_BTN_STYLE_REL, &selectedStyleOFF);
        lv_btn_set_style(btn, LV_BTN_STYLE_PR, &selectedStyleON); //set the pressed style
        lv_btn_set_style(btn, LV_BTN_STYLE_TGL_REL, &selectedStyleON); //set the toggle released style
        lv_btn_set_style(btn, LV_BTN_STYLE_TGL_PR, &selectedStyleOFF); //set the toggle pressed style
        }
    
    lv_obj_set_size(btn, buttonW, buttonH); //set the button size
    }

void createStyle(lv_style_t *style, lv_color_t color)
{
  lv_style_copy(style, &lv_style_plain);
  (*style).body.main_color = color;
  (*style).body.grad_color = color;
  (*style).body.radius = 0;
  (*style).text.color = DISPLAY_WHITE;
}

//------------------------------------------------------------------------------
void initializeGUI()
{
  initButtons();

	//----------------------------------------------------------------------------
	// Red Tab
	lv_page_set_scrl_layout(red_tab, LV_LAYOUT_GRID);

    createStyle(&redStyleOFF, DISPLAY_RED);
    createStyle(&redStyleON, DISPLAY_RED);

    for (int i = 0; i < NUM_SELECTION; i++)
    {
        lv_obj_set_free_num(redButtons[i], i+1);
        setStyle(redButtons[i], 1);
        lv_label_set_text(lv_label_create(redButtons[i], NULL), labelText[i+1]);
    }

	//----------------------------------------------------------------------------
	// Blue Tab
	lv_page_set_scrl_layout(blue_tab, LV_LAYOUT_GRID);

    createStyle(&blueStyleON, DISPLAY_BLUE);
    createStyle(&blueStyleOFF, DISPLAY_BLUE);

    for (int i = 0; i < NUM_SELECTION; i++)
    {
        lv_obj_set_free_num(blueButtons[i], i+1+NUM_SELECTION);
        setStyle(blueButtons[i], 2);
        lv_label_set_text(lv_label_create(blueButtons[i], NULL), labelText[i+1+NUM_SELECTION]);
    }

    //----------------------------------------------------------------------------
    // Other Tab
    lv_page_set_scrl_layout(skills_tab, LV_LAYOUT_GRID);

    createStyle(&skillsStyleON, DISPLAY_YELLOW);
    createStyle(&skillsStyleOFF, DISPLAY_YELLOW);

    for (int i = 0; i < NUM_SELECTION; i++)
    {
        lv_obj_set_free_num(otherButtons[i], i+1+(2*NUM_SELECTION));
        setStyle(otherButtons[i], 3);
        lv_label_set_text(lv_label_create(otherButtons[i], NULL), labelText[i+1+(2*NUM_SELECTION)]);
    }

  //----------------------------------------------------------------------------

  createStyle(&selectedStyleON, DISPLAY_PURPLE);
  createStyle(&selectedStyleOFF, DISPLAY_PURPLE);

	//----------------------------------------------------------------------------
  lv_tabview_set_tab_act(gui, 0, false);
}