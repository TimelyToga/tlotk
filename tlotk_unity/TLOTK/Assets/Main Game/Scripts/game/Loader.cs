using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Loader : MonoBehaviour {

	public GameObject statePrefab;

	// Use this for initialization
	void Awake () {
		if (State.instance == null) {
			Instantiate (statePrefab);
		}
	}
}
