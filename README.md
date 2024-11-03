⚠️ This is a fork of the original [EOS Integration Kit](https://github.com/betidestudio/EOSIntegrationKit) from Betide Studio.

This fork serves a very specific use case: adding Easy Anti-Cheat to a pre-existing PC game that uses Steam as the default subsystem via the Advanced Sessions Plugin. Easy Anti-Cheat requires the EOS subsystem to work properly, which creates some integration issues that this fork resolves.

There are instructions on how to integrate the EOS Integration Kit with Steam provided in the [official documentation](https://eik.betide.studio/integrations/steamintegrationkit). However, these instructions did not work for us in the specific case of adding Easy Anti-Cheat.

# Setup

## Plugin
Install this fork of the plugin by copying its contents into the `.\Plugins` folder of your Unreal Engine project.

## Config Files
In `DefaultEngine.ini`, set EIK as `NativePlatformService` and enable it:

```
[OnlineSubsystem]
DefaultPlatformService=Steam
NativePlatformService=EIK

[OnlineSubsystemEIK]
bEnabled=true
```

> We keep Steam as the `DefaultPlatformService`, which allows all Steam session-related functionalities and Unique Net IDs to continue working properly (otherwise, they would be taken over by EIK). In our experience, we still needed to specify EIK as the `NativePlatformService` to avoid editor crashes on EIK subsystem shutdown or compiled builds not exiting processes properly (leaving ghost processes hanging).
>
> There might be a better way to do this; however, the EIK plugin assumes it is used as a Platform Service, and if used as a standard subsystem, it will require some additional design changes.

## EOS Login
You need to log in to EOS for Anti-Cheat, and it cannot use a non-permanent identification method such as `DeviceId`. Therefore, follow [these instructions](https://eik.betide.studio/Authentication/methods/steam) to log in with a `Steam Session Ticket`.

The difference with this fork of EIK is that you will not get a `Product User ID` from the `Login Using Connect Interface node`. Instead, you will get a string `Client Product ID` that you MUST save for future reference (for example, in your Game Instance).

> In standard usage, the resulting ID is saved by EIK in the `Unique Net ID` of the Player Controller, which then gets replicated to all clients. However, since we are forcing Steam to be the Default Platform, the Unique Net IDs are set by Steam, not EIK. Therefore, we need to manually store these IDs on every client and pass them along at a later stage (see below).

## Plugin
Follow these tutorials:

* [Plugin Configuration](https://eik.betide.studio/getting-started/configuration)
* [Anti-Cheat Blueprint Setup](https://eik.betide.studio/multiplayer/anti-cheat)

There's also a [video](https://www.youtube.com/watch?v=PvO_2O6ikls) explaining the same concepts. While it is tagged as version `v3`, the same code seems to apply.

You will need to modify the resulting code in the following way:

* In the Game Mode blueprint, instead of the `OnPostLogin` event, create a new custom event, for example, called `Register EAC Client On Server`, which takes a `Player Controller` and a `Client Product ID` as input parameters. Plug these two inputs into EIK's node `Register Client for Anti Cheat` directly.
* In the Player Controller blueprint, create a new custom event, for example, called `Server Register EAC Client`, which takes a `Client Product ID` as an input parameter. The event must `Run on Server` reliably. This event calls the Game Mode's `Register EAC Client On Server` event defined in the previous point and passes the `Client Product ID` and `Self` as the Player Controller inputs.
* Still in the Player Controller blueprint, call this newly created event `Server Register EAC Client` after registering the client with EIK's node `Register Anti Cheat Client`, passing in the `Client Product ID `that you previously saved on every client after the EOS login.

> Basically, what we are doing is substituting the `OnPostLogin` functionality with a custom one so that we can pass along the EOS Client Product IDs of every client, which are not stored in the Player Controllers as Unique Net IDs since we use Steam as the Default Platform.

<br />
<hr />

<h1 align="center" id="title">EOS Integration Kit V4</h1>

<p align="center"><img src="https://socialify.git.ci/betidestudio/EOSIntegrationKit/image?description=1&amp;descriptionEditable=Integrate%20EOS%20in%20few%20clicks%2C%20or%20that%27s%20what%20we%20want%20%3B)&amp;font=Inter&amp;forks=1&amp;language=1&amp;name=1&amp;pattern=Plus&amp;stargazers=1&amp;theme=Auto" alt="project-image" width="600" height="338/"></p>

<p id="description">EIK (Epic Online Services Integration Kit) is a plugin that enables seamless integration between Epic Online Services (EOS) and Unreal Engine. The plugin provides access to the EOS SDK (Software Development Kit) within Unreal Engine allowing developers to easily implement features such as matchmaking achievements leaderboards and more.</p>

- [Discord Support](https://discord.gg/betidestudio)
- [Mail Support](mailto:support@betide.studio)
- [Unreal Engine Marketplace Version](https://www.unrealengine.com/marketplace/en-US/product/eos-integration-kit)

<h2>🚀 Setup Information</h2>

- [Video](https://www.youtube.com/watch?v=tCuE6YOg_-I)
- [Documentation](https://eik.betide.studio)

<h2>Project Screenshots:</h2>

<img src="https://cdn1.epicgames.com/ue/product/Screenshot/Copy%20of%20EOS%20Integration%20Kit-1920x1080-8892797d69c34f8413b3f6bcc2b31ab6.png?resize=1&amp;w=1920" alt="project-screenshot" width="450" height="253/"> <img src="https://cdn1.epicgames.com/ue/product/Screenshot/10-1920x1080-81ef29920c48e9dc8dcca0de5c2e9cbd.png?resize=1&amp;w=1920" alt="project-screenshot" width="450" height="253/">

<img src="https://cdn1.epicgames.com/ue/product/Screenshot/11-1920x1080-f5e47fae54b6ee180aa146c3f0f12d9d.png?resize=1&amp;w=1920" alt="project-screenshot" width="450" height="253/"> <img src="https://cdn1.epicgames.com/ue/product/Screenshot/FinalAsset%209-1920x1080-b48f833c4cb52358d223f31b52913157.png?resize=1&amp;w=1920" alt="project-screenshot" width="450" height="253/">

<h2>🧐 Features</h2>

Here're some of the project's best features:

*   Login and Signup
*   Lobbies and Matchmaking Sessions
*   Anti-Cheat supported (Client-Server Model)
*   Basic Host Migration
*   Friends & Social (Invites Overlay)
*   Save File Management
*   Web APIs
*   Title Storage
*   Player Storage
*   Player Stats
*   Leaderboards
*   Presence
*   Voice Chat \[ EOS Voice Integration Kit included with Positional Voice Chat\]
*   Android And Quest now supported natively.
*   Easy for beginners.

<h2>🛠️ Installation Steps:</h2>

Please check the docs for updated Installation Steps

<h2>🍰 Contribution Guidelines:</h2>

Being a open-source project it's important for the people to contribute to the plugin. The only guideline is to include all headers because 5.3 has a lot of issues with headers xD

  
  
<h2>💻 Built with</h2>

Technologies used in the project:

*   Unreal Engine
*   C++

<h2>🛡️ License:</h2>

This project is licensed under the MIT License

<h2>💖Like our work?</h2>

Consider supporting us at [Patreon](https://www.patreon.com/betide)
Hire us at [support@betide.studio](mailto:support@betide.studio)
