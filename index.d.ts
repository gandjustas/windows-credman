 declare module 'windows-credman'{
    export function getCredentials(targetname:string):{ username:string; password:string; }
 }