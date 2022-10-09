#include"world.h"
#include<tinyxml2.h>
using namespace tinyxml2;
#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

int save_settings(world *the_world, char *filename)
{

  XMLDocument xmlSettings;


  return 0;
}

int load_settings(world *the_world, char *filename)
{

  XMLDocument xmlSettings;
  XMLError eResult = xmlSettings.LoadFile(filename);
  XMLCheckResult(eResult);

  XMLNode * pRoot = xmlSettings.FirstChild();
  if (pRoot == nullptr) return XML_ERROR_FILE_READ_ERROR;

  XMLElement * pElement;

  pElement = pRoot->FirstChildElement("mutation");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
  eResult = pElement->QueryIntText(&the_world->mutation);
  XMLCheckResult(eResult);

  pElement = pRoot->FirstChildElement("addsub");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
  eResult = pElement->QueryIntText(&the_world->addsub_mutation);
  XMLCheckResult(eResult);

  pElement = pRoot->FirstChildElement("death_age");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
  eResult = pElement->QueryIntText(&the_world->death_age);
  XMLCheckResult(eResult);

  pElement = pRoot->FirstChildElement("grass_food");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
  eResult = pElement->QueryIntText(&the_world->grass_food);
  XMLCheckResult(eResult);

  pElement = pRoot->FirstChildElement("grass_grow");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
  eResult = pElement->QueryIntText(&the_world->grass_grow);
  XMLCheckResult(eResult);

  pElement = pRoot->FirstChildElement("min_size");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
  eResult = pElement->QueryIntText(&the_world->min_size);
  XMLCheckResult(eResult);

  pElement = pRoot->FirstChildElement("carrion_fade");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
  eResult = pElement->QueryIntText(&the_world->carrion_fade);
  XMLCheckResult(eResult);

  pElement = pRoot->FirstChildElement("stay_cost");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
  eResult = pElement->QueryFloatText(&the_world->stay_cost);
  XMLCheckResult(eResult);

  pElement = pRoot->FirstChildElement("turn_cost");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
  eResult = pElement->QueryFloatText(&the_world->turn_cost);
  XMLCheckResult(eResult);

  pElement = pRoot->FirstChildElement("go_cost");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
  eResult = pElement->QueryFloatText(&the_world->go_cost);
  XMLCheckResult(eResult);

  pElement = pRoot->FirstChildElement("bump_cost");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
  eResult = pElement->QueryFloatText(&the_world->bump_cost);
  XMLCheckResult(eResult);

  pElement = pRoot->FirstChildElement("eat_cost");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
  eResult = pElement->QueryFloatText(&the_world->eat_cost);
  XMLCheckResult(eResult);

  pElement = pRoot->FirstChildElement("clone_cost");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
  eResult = pElement->QueryFloatText(&the_world->clone_cost);
  XMLCheckResult(eResult);

  pElement = pRoot->FirstChildElement("attack_cost");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
  eResult = pElement->QueryFloatText(&the_world->attack_cost);
  XMLCheckResult(eResult);

  pElement = pRoot->FirstChildElement("work_ratio");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
  eResult = pElement->QueryFloatText(&the_world->work_ratio);
  XMLCheckResult(eResult);

  pElement = pRoot->FirstChildElement("steal_food");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
  eResult = pElement->QueryBoolText(&the_world->steal_food);
  XMLCheckResult(eResult);


  return 0;
}
