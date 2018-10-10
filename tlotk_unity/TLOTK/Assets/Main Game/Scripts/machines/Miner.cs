using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Miner : IMachine, ResourceStream
{
	public bool curPlacing = true;
	public GameObject asteroid;
	private AlignToGrid aligner;
	private Asteroid2D asteroid2D;
	private MultipleInputStream stream;

	private List<Tile> resourceSources;

	void placeAt ()
	{
		asteroid2D.positionToTile (0, 0);
	}

	// Use this for initialization
	void Start ()
	{
		aligner = asteroid.GetComponent<AlignToGrid> () as AlignToGrid;
		asteroid2D = asteroid.GetComponent<Asteroid2D> ();
		// curPlacing = true;

		// Initialize sources 
	}
	
	// Update is called once per frame
	void Update ()
	{
		if (curPlacing) {
			// Follow mouse 
			Vector3 mousePos = Input.mousePosition;
			mousePos = new Vector3 (mousePos.x, mousePos.y, Camera.main.transform.position.z);
			Vector3 worldPos = Camera.main.ScreenToWorldPoint (mousePos);
			worldPos.z = 0.0f;

			asteroid2D.positionToTile (worldPos.x, worldPos.y);

			// If click then place 
			Vector3 alignedWorldPos = aligner.getAligned (worldPos);
			transform.position = alignedWorldPos;

			if (Input.GetMouseButtonUp (0)) {
				curPlacing = false;
			}
		}
	}

	// Override

	public ResourcePack getSourceSample(float amt) {
		return stream.getSourceSample (amt);
	}

	public void outputResource(ResourcePack rp) {
		stream.outputResource (rp);
	}
}

