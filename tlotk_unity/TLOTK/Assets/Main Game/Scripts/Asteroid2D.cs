using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Asteroid2D : MonoBehaviour {

	public List<GameObject> tiles = new List<GameObject> ();
	private float[] bounds = {0.4f, 0.3f, 0.27f, 0.03f};

	public Transform player;

	private Vector3 center;


	private float FADE_RANGE = 170.0f;
	private float MAX_RANGE = 300.0f;
	private float FADE_START;
	public int WIDTH = 10;
	public int HEIGHT = 12;
	public GameObject[] mTiles;

	GameObject pickTile() {
		float r = Random.value;
		for(int a = 0; a < bounds.Length; a++) {
			if(r <= bounds[a]) {
				return tiles[a];
			}
			r -= bounds[a];
		}

		return tiles[0];
	}

	// Use this for initialization
	void Start () {
		FADE_START = MAX_RANGE - FADE_RANGE;
		mTiles = new GameObject[WIDTH * HEIGHT];

		for (int x = 0; x < WIDTH; x++) {
			for (int y = 0; y < HEIGHT; y++) {
				int i = x + y * WIDTH;
				mTiles[i] = Instantiate (pickTile());
				mTiles [i].transform.SetParent (this.transform);
				mTiles[i].transform.position = new Vector3 (50 * x, 50 * y, 0);
			}
		}
		for (int a = 0; a < mTiles.Length; a++) {
			
		}

		center = new Vector3 ((WIDTH * 50) / 2.0f, (HEIGHT * 50) / 2.0f, 0) + transform.position;
	}

	// Update is called once per frame
	void Update () {
		scan (player.position);
	}

	void scan(Vector3 position) {
		for (int a = 0; a < mTiles.Length; a++) {
			GameObject cur = mTiles [a];
			Tile tile = cur.GetComponent<Tile> ();
			Vector3 dist = position - cur.transform.position;
			// cur.gameObject.SetActive (dist.magnitude < MAX_RANGE);
			if (dist.magnitude < MAX_RANGE) {
				if (dist.magnitude > FADE_START) {
					float curOpacity = 1.0f - (dist.magnitude - FADE_START) / FADE_RANGE;
					tile.setTileOpacity (curOpacity);
				}
			} else {
				tile.setTileOpacity (0.0f);
			}
		}
	}
}
