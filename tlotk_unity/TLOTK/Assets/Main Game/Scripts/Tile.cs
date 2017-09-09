using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Tile : ResourceStream { 

	public GameObject sprite;
	private ResourcePack resources;

	// How hard it is to mine
	private float extractionDiff;
	public readonly float MIN_EXTRACT = 1.0f;

	public Tile(ResourcePack rp, float eDiff) {
		resources = rp;
		extractionDiff = eDiff;
	}

	void Start() {

	}
	
	// Update is called once per frame
	void Update () {
		
	}
		
	public ResourcePack getSourceSample(float amt) {
		return resources.getBalancedSample (amt);
	}

	public void outputResource(ResourcePack rp) {
		// No-op: you can't add infuse resources into a Tile
	}
}
