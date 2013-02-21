<?php

/**
 * Allows other modules to respond when Snape performs some action on the Marauder's map.
 *
 * @param string $event
 *   Identifies the action performed by Snape on the Marauder's map.
 *   Can be one of "open_map" or "close_map".
 */
function hook_design_patterns_observer_notify($event) {
	if ($event == 'open_map') {
		// Map has been opened.
	}
	elseif ($event == 'close_map') {
		// Map has been closed.
	}
}