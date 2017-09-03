using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ModalScript : MonoBehaviour {

    public GameObject modalWindow;

	// Use this for initialization
	public void clicked(UnityEngine.UI.Button button)
    {
    	Debug.Log("Activating modal!");
    	modalWindow.SetActive(true);
	}
}
