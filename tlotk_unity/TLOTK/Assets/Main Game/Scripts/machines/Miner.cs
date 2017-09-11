using UnityEngine;
using System.Collections;

public class Miner : IMachine
{
	public bool curPlacing = true;
	public GameObject asteroid;
	private AlignToGrid aligner;

	void placeAt() {

	}

	// Use this for initialization
	void Start ()
	{
		aligner = asteroid.GetComponent<AlignToGrid> () as AlignToGrid;
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

			// If click then place 
			Vector3 alignedWorldPos = aligner.getAligned(worldPos);
			transform.position = alignedWorldPos;

			if (Input.GetMouseButtonUp (0)) {
				curPlacing = false;
			}
		}
	}
}

