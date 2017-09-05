﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AsteroidField : MonoBehaviour {


	public int numAsteroids = 10;
	public int AVERAGE_SIZE = 10;
	public int SIZE = 10;

	private int MAX_TRIES = 100;

	// Use this for initialization
	void Start () {

		for (int x = 0; x < SIZE; x++) {
			for (int y = 0; y < SIZE; y++) {
				Debug.Log ("AA");
				AsteroidGeneration a = new AsteroidGeneration ();
				// a.Translate (new Vector3(x * 600.0f, y * 600.0f, 0.0f));
				a.transform.SetParent (transform);
			}
		}
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	private bool rBool() {
		return (Random.value > 0.5f);
	}

	private int rRange(int lower, int upper) {
		return rInt (upper - lower) + lower;
	}

	private int rInt(int bound) {
		return (int) Mathf.Floor (Random.value * (bound + 1));
	}
}
