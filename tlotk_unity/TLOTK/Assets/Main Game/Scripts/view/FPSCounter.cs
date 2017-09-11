using UnityEngine;
using System.Collections;

public class FPSCounter : MonoBehaviour
{
	float deltaTime = 0.0f;
	Vector3 pos = Vector3.zero;
	Vector3 previousPos = Vector3.zero;
	float speed = 0.0f;

	void Update()
	{
		deltaTime += (Time.deltaTime - deltaTime) * 0.1f;
		previousPos = pos;
		pos = Camera.main.transform.position;
		speed = (pos - previousPos).magnitude / deltaTime;
	}

	void OnGUI()
	{
		int w = Screen.width, h = Screen.height;

		GUIStyle style = new GUIStyle();

		Rect rect = new Rect(0, 0, w, h * 2 / 100);
		style.alignment = TextAnchor.UpperLeft;
		style.fontSize = h * 2 / 50;
		style.normal.textColor = new Color (1.0f, 1.0f, 1.0f, 1.0f);
		float msec = deltaTime * 1000.0f;
		float fps = 1.0f / deltaTime;
		string text = string.Format("{0:0.0} ms ({1:0.} fps)\n({2:0.}, {3:0.}\n({4:0.0} m/s))", msec, fps, pos.x, pos.y, speed);
		GUI.Label(rect, text, style);
	}
}