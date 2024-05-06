# SOC_Project
Automatic Clock gating on OpenROAD framework
---
abstract: |
  In digital integrated circuit design, achieving a balance between
  power efficiency, performance, and area optimization is paramount.
  This project presents an automated clock gating algorithm integrated
  into the OpenROAD framework to facilitate the development of
  tape-out-ready chips. Leveraging clock gating, which diminishes
  dynamic power consumption by deactivating the clock in dormant
  segments of the circuit, the algorithm aims to bolster power
  efficiency. Implementing automated clock gating after netlist
  generation involves analyzing the netlist to identify signals that can
  be used as enable signals for clock gating, inserting clock gating
  logic into the netlist, and then writing out the modified netlist with
  the added clock gating logic. This approach can be implemented using
  scripting languages, enabling designers to achieve power-efficient
  designs without the need for additional synthesis steps. Evaluation of
  key design metrics, including power consumption, synthesized area,
  place-and-route area, and die area, relative to the percentage of
  gated registers, elucidates the algorithm’s impact and trade-offs.
  
Authors:
- Ansh Bhatnagar (ab10741@nyu.edu)
- Dhana Laxmi Sirigireddy (ds6992@nyu.edu)
- Jayanth Rajaram Sastry  (js12891@nyu.edu)
---

![Slide1](https://github.com/D-girl-11t/SOC_Project/assets/63849382/bef74ec3-4424-4427-9bc2-26d50cbb946c)
![Slide2](https://github.com/D-girl-11t/SOC_Project/assets/63849382/672a7534-857b-4c66-a4bd-891cb20edc4d)
![Slide3](https://github.com/D-girl-11t/SOC_Project/assets/63849382/a59c574d-1787-46ed-ba96-3f4a15ff7a99)
![Slide4](https://github.com/D-girl-11t/SOC_Project/assets/63849382/cdcfef6b-a7bb-473b-9b27-367d192f5b34)
![Slide5](https://github.com/D-girl-11t/SOC_Project/assets/63849382/0b6a5523-47ff-4ccd-b725-bc64f2862f60)
![Slide6](https://github.com/D-girl-11t/SOC_Project/assets/63849382/5494f29d-0863-4ad4-a9f1-65baf4e60cd8)
![Slide7](https://github.com/D-girl-11t/SOC_Project/assets/63849382/2b034342-4fc3-440c-8452-5779e41663d6)
![Slide8](https://github.com/D-girl-11t/SOC_Project/assets/63849382/7176744d-954d-466f-9e8a-7f6ec6fdb3f1)
![Slide9](https://github.com/D-girl-11t/SOC_Project/assets/63849382/4572531e-b88d-49d7-80f8-a945f53a952b)
![Slide10](https://github.com/D-girl-11t/SOC_Project/assets/63849382/9991e22f-fbdb-4cfa-bd1e-3c603741e4eb)
![Slide11](https://github.com/D-girl-11t/SOC_Project/assets/63849382/fca69860-59f4-4f4b-ad5a-ab0ca8193b50)
![Slide12](https://github.com/D-girl-11t/SOC_Project/assets/63849382/496e82e8-64f4-4d33-a10b-fd7b215a41f0)
![Slide13](https://github.com/D-girl-11t/SOC_Project/assets/63849382/7b930fbc-2999-4354-823a-fc8f0a68f538)
![Slide14](https://github.com/D-girl-11t/SOC_Project/assets/63849382/80a581b2-e060-4a11-b69a-5c47def00a48)
![Slide15](https://github.com/D-girl-11t/SOC_Project/assets/63849382/33caf79e-3c7e-44c7-8ad6-0d1f6d4f4221)
![Slide16](https://github.com/D-girl-11t/SOC_Project/assets/63849382/a37974cc-09dd-48a0-8277-dfddb4e4520c)
![Slide17](https://github.com/D-girl-11t/SOC_Project/assets/63849382/cb46c6db-1902-4427-beb5-84f026643598)
![Slide18](https://github.com/D-girl-11t/SOC_Project/assets/63849382/4ec7d6cf-db59-433d-9839-8f410305a6d4)
![Slide19](https://github.com/D-girl-11t/SOC_Project/assets/63849382/2f6b718f-625c-42cb-ad45-290e5e0a3586)
![Slide20](https://github.com/D-girl-11t/SOC_Project/assets/63849382/d8fb1808-7177-48f6-831a-c53735e31668)
![Slide21](https://github.com/D-girl-11t/SOC_Project/assets/63849382/c7d9b7b7-ff32-483b-9609-b60f091c9e17)


