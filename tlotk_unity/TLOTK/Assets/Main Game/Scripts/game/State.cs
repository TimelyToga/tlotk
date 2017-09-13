using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class State : MonoBehaviour {

	public static State instance = null;

	public State getInstance() {
		if (instance == null) {
			instance = this;
		} else if (instance != this) {
			Destroy (gameObject);
		}

		return instance;
	}

	// Use this for initialization
	void Awake () {
		getInstance ();
		DontDestroyOnLoad (gameObject);
	}

	
}
