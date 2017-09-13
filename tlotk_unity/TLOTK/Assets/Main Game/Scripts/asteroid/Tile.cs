using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Tile : MonoBehaviour, ResourceStream { 

	public GameObject sprite;
	private ResourcePack resources;
	private SpriteRenderer sRenderer;

	// How hard it is to mine
	private float extractionDiff;
	public readonly float MIN_EXTRACT = 1.0f;

	public Tile(ResourcePack rp, float eDiff) {
		resources = rp;
		extractionDiff = eDiff;
	}

	void Start() {
		sRenderer = sprite.GetComponent<SpriteRenderer> ();
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

	public void setTileOpacity(float vis) {
		Color newColor = sRenderer.color;
		newColor.a = vis;
		sRenderer.color = newColor;
	}
}
