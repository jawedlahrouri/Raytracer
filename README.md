[![Academic Year](https://img.shields.io/badge/Epitech-Tek2-green?style=for-the-badge&logo=epitech&logoColor=white)](https://www.epitech.eu/)
[![Language: C++20](https://img.shields.io/badge/Language-C%2B%2B20-00599C.svg?style=for-the-badge&logo=c%2B%2B)](https://en.wikipedia.org/wiki/C%2B%2B20)
[![Module](https://img.shields.io/badge/Module-G--OOP--400-informational?style=for-the-badge)](#)

# 🌟 Raytracer — Moteur de Rendu 3D Photoréaliste en C++20

**Raytracer** est un moteur de lancer de rayons 3D conçu en **C++20**. Il synthétise des images réalistes en simulant le trajet inverse de la lumière depuis l'observateur (caméra) vers les sources lumineuses à travers une scène géométrique, modélisant réflexions, réfractions, ombres portées et éclairages complexes.

---

## 🚀 Capacités & Fonctionnalités Avancées

- **Primitives Géométriques 3D** :
  - Sphères (`SpherePrimitive`)
  - Plans infinis (`PlanePrimitive`)
  - Cylindres finis/infinis (`CylinderPrimitive`)
  - Cônes (`ConePrimitive`)
  - Rectangles et parallélogrammes orientés (`RectPrimitive`)
- **Matériaux & Modèles d'Illumination** :
  - **Flat Shading** : Teinte unie sans calcul de brillance.
  - **Phong Shading** : Éclairage ambiant, diffus (Lambert) et spéculaire.
  - **Matériau Métallique & Réflexions** : Réflexion miroir de l'environnement avec indice d'atténuation.
  - **Matériau Transparent & Réfraction** : Modélisation du verre et de l'eau avec indice de réfraction de Snell-Descartes.
- **Sources de Lumière Multiples** :
  - Lumière ambiante globale (`AmbientLight`).
  - Lumières ponctuelles (`PointLight`).
  - Lumières directionnelles solaires (`DirectionalLight`).
  - Lumières colorées dynamiques (`ColoredLight`).
- **Accélération Spatiale & Performance** :
  - **BVH (*Bounding Volume Hierarchy*)** et boîtes englobantes alignées sur les axes (**AABB**) pour réduire la complexité des intersections rayon-objet de $O(N)$ à $O(\log N)$.
- **Effets Optiques** :
  - Anti-aliasing par sur-échantillonnage (*Supersampling / MSAA*).
- **Sorties & Visualisation** :
  - Fenêtre interactive en direct avec la bibliothèque SFML (`sfml_display`).
  - Export d'image sans perte au format PPM haute fidélité (`ppm_export`).

---

## 📄 Format de Configuration d'une Scène (`.cfg`)

Les scènes 3D sont décrites dans des fichiers de configuration textuels simples :

```text
camera: {
    resolution = { width = 1920; height = 1080; };
    position = { x = 0.0; y = -100.0; z = 20.0; };
    rotation = { x = 0.0; y = 0.0; z = 0.0; };
    fov = 60.0;
};

primitives: {
    spheres = (
        { x = 0.0; y = 50.0; z = 0.0; r = 15.0; color = { r = 255; g = 50; b = 50; }; material = "phong"; },
        { x = 30.0; y = 70.0; z = -5.0; r = 10.0; color = { r = 200; g = 200; b = 255; }; material = "reflection"; }
    );
    planes = (
        { axis = "Z"; position = -20.0; color = { r = 120; g = 120; b = 120; }; material = "flat"; }
    );
};

lights: {
    ambient = 0.2;
    diffuse = 0.8;
    point = (
        { x = 40.0; y = 0.0; z = 50.0; intensity = 1.0; }
    );
};
```

---

## 🛠️ Compilation & Utilisation

```bash
make        # Génère l'exécutable 'raytracer'
make clean  # Nettoie les fichiers objets temporaires
make fclean # Supprime les fichiers compilés
make re     # Recompile le moteur

# Lancer le rendu d'une scène
./raytracer scenes/demo.cfg
```
