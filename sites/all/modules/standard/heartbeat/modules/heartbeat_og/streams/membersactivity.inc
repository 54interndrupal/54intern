<?php

/**
 * @file
 *   Defines a stream for Member Activity.
 */

/**
 * Concrete class MembersActivity
 *   Defines a stream displaying all activity from members in a group.
 */
class MembersActivity extends HeartbeatStream {

  protected $nid = 0;
  protected $og_context = NULL;
  protected $group = NULL;

  public function construct() {
    $this->detectGroup();
  }

  /**
   * detectGroup
   *
   * Detects the group for a given node ID.
   */
  private function detectGroup() {

    // Set the group via current group context.
    if ($og_context = og_context()) {
      $this->og_context = $og_context;
      $this->setGroup($og_context->etid);
    }

  }

  /**
   * setGroup
   *
   * Sets the group for a given node ID.
   * @param Integer $nid
   *   The group node ID.
   */
  private function setGroup($nid) {
    $this->nid = $nid;
    $this->group = node_load($this->nid);
  }

  /**
   * hasAccess
   *
   * @param $text
   * @return boolean to indicate the access to the stream
   */
  public function hasAccess() {
    return $this->nid > 0 ? TRUE : FALSE;
  }

  /**
   * Implementation of queryAlter().
   */
  protected function queryAlter() {

    $members = array();
    $result = db_query("SELECT etid as uid FROM {og_membership} WHERE entity_type = 'user' and gid = :gid ", array(':gid' => $this->og_context->gid));
    foreach ($result as $row) {
      $members[$row->uid] = $row->uid;
    }

    $this->query->condition('ha.in_group', 0, '>');
    $this->query->condition('ha.uid', $members, 'IN');

  }

}
