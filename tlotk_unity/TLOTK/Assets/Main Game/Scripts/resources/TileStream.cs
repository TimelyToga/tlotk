using UnityEngine;
using System.Collections;

public class TileStream : ResourceStream
{
	private ResourcePack resources;

	// How hard it is to mine
	private float extractionDiff;
	public readonly float MIN_EXTRACT = 1.0f;

	public TileStream(ResourcePack res, float eDiff) {
		resources = res;
		extractionDiff = eDiff;
	}

	// Use this for initialization
	void Start ()
	{
		
	}
	
	// Update is called once per frame
	void Update ()
	{
	
	}

	ResourcePack resourceSource() {

	}

	void outputResource(ResourcePack rp) {
		// No-op
	}
}

