using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MenuNavigator : MonoBehaviour {

	public GameObject pMiner;
	public GameObject asteroid;
	private GameObject curReference;

	// Use this for initialization
	void Start () {
		
	}

	void createNewObject(GameObject prefab) {
		if (curReference != null) {
			Destroy (curReference);
		}

		curReference = Instantiate (prefab);
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetKeyUp (KeyCode.B)) {
			Miner miner = pMiner.GetComponent<Miner> () as Miner;
			miner.asteroid = asteroid;
			createNewObject (pMiner);
		}
	}
}
