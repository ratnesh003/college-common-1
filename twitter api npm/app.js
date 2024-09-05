import { TwitterApi } from 'twitter-api-v2';

// OAuth 1.0a (User context)
const userClient = new TwitterApi({
    appKey: 'oKxF1x9hupr9FsVefzsC1ZasQ',
    appSecret: 'dY8y7BXRjVn8UKhGL4e6vROyI9Dnntsw5IvnmRCQMJkrvHrsAa',
    // Following access tokens are not required if you are
    // at part 1 of user-auth process (ask for a request token)
    // or if you want a app-only client (see below)
    accessToken: '1745862167038230532-vGVAiCWCRa7CTYsXjrGKExA2xZMiqv',
    accessSecret: 'G3kunuBoXhcfM1GNo0NLik5Y0zi9FKOuO9fwPg4eFbMEQ',
});

// OAuth2 (app-only or user context)
// Create a client with an already known bearer token
const appOnlyClient = new TwitterApi('AAAAAAAAAAAAAAAAAAAAAClsvQEAAAAA3LUz9j%2FMbPlK0Kritk8zjrIyQSQ%3DoNB65Y71DKqXrhyk7Oahg4I2PHFUIxeQ8TCkhNmHtTCxylQZqV');
// OR - you can also create a app-only client from your consumer keys -
const appOnlyClientFromConsumer = await userClient.appLogin();
console.log(appOnlyClient)
console.log(appOnlyClientFromConsumer)