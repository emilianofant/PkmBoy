#pragma once

#include "Resources.h"
#include "Components.h"

/**
 * @brief Class that defines a Trigger component, which basically
 *        will have a position in the map, and could be triggered
 *        when the player position matches the trigger position.
 *
 *        @todo: manage a block to prevent loop triggers.
 */
class TriggerComponent : public Component
{
private:
  /**
   * @brief The local reference to a type struct with the data
   *        that defines the Trigger.
   */
  triggersDefinition_t *_trigger;
public:
  /**
   * @brief Construct a new Trigger Component object
   *
   * @param trEnum  Id of the specific trigger.
   */
  TriggerComponent(triggerEnum_t trEnum)
  {
    _trigger = &triggersDefinitions[trEnum];
  }

  /**
   * @brief This function will execute any function defined in the
   *        Triggers (like a callback).
   */
  void doAction()
  {
    _trigger->action();
  }
};
